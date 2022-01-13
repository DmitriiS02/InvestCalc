<script>
  import {link} from "svelte-spa-router";
  import {fade} from "svelte/transition";
  import Fa from 'svelte-fa';
  import {faTrash, faPlus, faArrowLeft} from '@fortawesome/free-solid-svg-icons';
  import {beforeUpdate, afterUpdate} from 'svelte';
  import {slide} from 'svelte/transition';
  import Color from 'color';
  import { chart } from "svelte-apexcharts";
  import Chart from 'svelte-frappe-charts';

  let data = {
    labels: ['Sun', 'Mon', 'Tues', 'Wed', 'Thurs', 'Fri', 'Sat'],
    datasets: [
      {
        values: [10, 12, 3, 9, 8, 15, 9]
      }
    ]
  };

  const DATA_COUNT = 7;
  const NUMBER_CFG = {count: DATA_COUNT, min: -100, max: 100};
  let years = 10;

  let options = {
    chart: {
      type: "bar",
    },
    series: [
      {
        name: "sales",
        data: [30, 40, 35, 50, 49, 60, 70, 91, 125],
      },
    ],
    xaxis: {
      categories: [1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999],
    },
  };

  function calcComplexPercent(startSum, percent){
    let factor = percent / 100 + 1;
    let points = []
    for (let year of getYears(years)) {
      points.push(startSum);
      startSum *= factor;
    }
    return points;
  }

  const randomInt = (min, max) => {
    return Math.floor(Math.random() * (max - min + 1)) + min;
  };

  const getRandomColor = () => {
      let h = randomInt(0, 360);
      let s = randomInt(42, 98);
      let l = randomInt(40, 90);
      return `hsl(${h},${s}%,${l}%)`
  };

  let inputData = [
    {name: "ОФЗ", percent: 8, color: getRandomColor(), start: 100_000},
    {name: "Акции", percent: 15, color: getRandomColor(), start: 50_000},
    {name: "Опционы", percent: 30, color: getRandomColor(), start: 20_000},
    {name: "Облигации", percent: 10, color: getRandomColor(), start: 100_000},
  ];
  function getYears(amount) {
    let years = []
    let currentYear = (new Date()).getFullYear();
    for (let i of Array(amount).keys()) {
      years.push(currentYear + i);
    }
    return years
  }
  function recalculate() {
    let data = {
      labels: getYears(years),
      datasets: [],
      responsive: true,
    }

    for (let instrument of inputData) {
      data.datasets.push({
        fill: true,
        lineTension: 0.3,
        borderJoinStyle: 'miter',
        label: instrument.name,
        borderColor: instrument.color,
        backgroundColor: Color(instrument.color).fade(0.2).string(),
        pointBorderColor: instrument.color,
        pointBackgroundColor: instrument.color,
        data: calcComplexPercent(instrument.start, instrument.percent)
      });
    }
    return data
  }
  //
  // $: {
  //   years, inputData;
  //   data = recalculate();
  // }

  let scrollList;
  let autoscroll
  beforeUpdate(() => {
    autoscroll = scrollList && (scrollList.offsetHeight + scrollList.scrollTop) > (scrollList.scrollHeight - 20);
  });

  afterUpdate(() => {
    if (autoscroll) scrollList.scrollTo(0, scrollList.scrollHeight);
  });
</script>

<div class="grid place-items-center h-full">
  <div in:fade={{delay: 300}} class="w-9/12 max-w-screen-lg flex-col">
    <a class="btn btn-outline" href="/" use:link><Fa icon={faArrowLeft} style="margin-right: 5px"/>Назад</a>
<!--    <Line {data} options={{scales: {x: {stacked: true,}, y: {stacked: true}}}}/>-->
    <div use:chart={options}></div>
    <Chart data={data} type="line" />

    <div class="flex justify-center my-4">
      <button class="btn btn-outline btn-sm mx-2" on:click={() => years--}>Удалить год</button>
      <button class="btn btn-outline btn-sm mx-2" on:click={() => years++}>Добавить год</button>
    </div>
    <div class="grid place-items-center">
      <div class="flex flex-row my-3 space-x-20">
        <span class="p-3 badge badge-md">Инструмент</span>
        <span class="p-3 badge badge-md">Стартовая сумма</span>
        <span class="p-3 badge badge-md">Процент годовых</span>
      </div>
      <div bind:this={scrollList} class="flex flex-col items-center overflow-y-auto w-full h-80">
      {#each inputData as {name, percent, start}, i}
        <div class="flex flex-row my-3 space-x-7" transition:slide|local>
          <input placeholder="Название инструмента" bind:value={name} class="mx-2 input shrink input-bordered">
          <input placeholder="Стартовая сумма" bind:value={start} class="mx-2 input shrink input-bordered">
          <label class="input-group input-group">
            <input placeholder="11" bind:value={percent} class="input input-bordered w-16">
            <span>%</span>
          </label>
          <button class="btn btn-outline mx-1" on:click={() => {inputData.splice(i, 1); inputData = inputData}}>
            <Fa icon={faTrash} />
          </button>
        </div>
      {/each}
      </div>
      <button class="btn btn-sm mx-auto" on:click={
        () => inputData = inputData.concat({name: "", start: 0, percent: 0, color: getRandomColor()})
      }>
        <Fa icon={faPlus}/>
      </button>
    </div>
  </div>
</div>
