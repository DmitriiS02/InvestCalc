<script>
  import Router from 'svelte-spa-router';
  import Index from './Index.svelte';
  import Charts from './Charts.svelte';

  const routes = {
    '/': Index,
    '/charts': Charts
  }
</script>

<Router {routes}/>

<style lang="postcss" global>
  @tailwind base;
  @tailwind components;
  @tailwind utilities;
</style>