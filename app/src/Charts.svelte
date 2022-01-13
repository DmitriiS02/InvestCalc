<script>
  import {link} from "svelte-spa-router";
  import {fade} from "svelte/transition";
  import Fa from 'svelte-fa';
  import {faTrash, faPlus, faArrowLeft} from '@fortawesome/free-solid-svg-icons';
  import {beforeUpdate, afterUpdate} from 'svelte';
  import {slide} from 'svelte/transition';
  import ColorScheme from 'color-scheme';
  import { chart } from "svelte-apexcharts";
  import {writable} from 'svelte/store';

  const DATA_COUNT = 7;
  const NUMBER_CFG = {count: DATA_COUNT, min: -100, max: 100};
  let years = 10;
  let options;

  function calcComplexPercent(startSum, percent){
    let factor = percent / 100 + 1;
    let points = []
    for (let year of getYears(years)) {
      points.push(Math.floor(startSum));
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

  let savedData  = JSON.parse(localStorage.getItem('data')) || [
    {name: "ОФЗ", percent: 8, color: getRandomColor(), start: 100_000},
    {name: "Акции", percent: 15, color: getRandomColor(), start: 50_000},
    {name: "Опционы", percent: 30, color: getRandomColor(), start: 20_000},
    {name: "Облигации", percent: 10, color: getRandomColor(), start: 100_000},
  ];

  let inputData = writable(savedData);
  inputData.subscribe(update => localStorage.setItem('data', JSON.stringify(update)));
  const zip = (a, b) => a.map((k, i) => [k, b[i]]);

  const scheme =  new ColorScheme;
  scheme
    .from_hue(randomInt(30, 200))
    .scheme('triade')
    .variation('soft');
  const colors = scheme.colors().map(color => "#" + color);

  function getYears(amount) {
    let years = []
    let d = new Date();
    let year = d.getFullYear();
    let month = d.getMonth();
    let day = d.getDay();

    for (let i of Array(amount).keys()) {
      years.push((new Date(year + i, month, day)).valueOf());
    }
    return years
  }
  function recalculate() {

    let options = {
      series: [],
      chart: {
        type: 'area',
        height: 350,
        stacked: true,
        colors,
        stroke: {
          curve: 'smooth'
        },
        fill: {
          type: 'gradient',
          gradient: {
            opacityFrom: 0.6,
            opacityTo: 0.8,
          }
        },
      },
      dataLabels: {
        enabled: false
      },
      xaxis: {
        type: 'datetime'
      },
      tooltip: {
        x: {
          format: 'yyyy'
        },
      },
      title: {
        text: 'Расчет сложного процента',
        align: 'center'
      },
    }


    for (let instrument of $inputData) {

      let data = zip(getYears(years), calcComplexPercent(instrument.start, instrument.percent))
      options.series.push({
        name: instrument.name,
        data
      });
    }
    return options
  }
  //
  $: {
    years, $inputData;
    console.log('updated')
    options = recalculate();
  }

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
    {#key options}
      <div use:chart={options}></div>
    {/key}
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
      {#each $inputData as {name, percent, start}, i}
        <div class="flex flex-row my-3 space-x-7" transition:slide|local>
          <input placeholder="Название инструмента" bind:value={name} class="mx-2 input shrink input-bordered">
          <input placeholder="Стартовая сумма" bind:value={start} class="mx-2 input shrink input-bordered">
          <label class="input-group input-group">
            <input placeholder="11" bind:value={percent} class="input input-bordered w-16">
            <span>%</span>
          </label>
          <button class="btn btn-outline mx-1" on:click={() => {$inputData.splice(i, 1); $inputData = $inputData}}>
            <Fa icon={faTrash} />
          </button>
        </div>
      {/each}
      </div>
      <button class="btn btn-sm mx-auto" on:click={
        () => $inputData = $inputData.concat({name: "", start: 0, percent: 0, color: getRandomColor()})
      }>
        <Fa icon={faPlus}/>
      </button>
    </div>
  </div>
</div>
