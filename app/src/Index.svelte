<script>
  import {link} from 'svelte-spa-router'
  import Fa from 'svelte-fa';
  import {faBriefcase} from '@fortawesome/free-solid-svg-icons';
  import {fly, fade} from 'svelte/transition';
</script>

<div class="flex flex-col items-center justify-center h-screen">
  <h1
    in:fly={{y: 20, duration: 1000}}
    out:fade={{duration: 200}}
    class="text-4xl font-bold mb-5">
    Калькулятор инвестиций 💰!!!
  </h1>

  <p
    in:fly={{y: 20, duration: 1000}}
    out:fade={{duration: 200}}
    class="mb-5">
    Удобный способ оценить перспективы своих вложений
  </p>

  <a
    href="/charts" use:link
    class="btn"
    in:fly={{y:20, duration: 500, delay: 500}}
    out:fade={{duration: 200}}>
    <Fa icon={faBriefcase} style="margin-right: 5px"/>
    Рассчитать портфель
  </a>
</div>