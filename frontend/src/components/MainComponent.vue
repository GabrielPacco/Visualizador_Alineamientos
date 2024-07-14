<template>
    <div class="container">
      <h1>Visualizador de Alineamientos</h1>
      <ul class="nav">
        <li @click="navigateTo('global')" :class="{ active: currentComponent === 'GlobalAlignment' }">Alineamiento Global</li>
        <li @click="navigateTo('verificar')" :class="{ active: currentComponent === 'VerificarCadenas' }">Verificar Cadenas</li>
        <li @click="navigateTo('estrella')" :class="{ active: currentComponent === 'AlineamientoEstrella' }">Alineamiento Estrella</li>
      </ul>
      <div class="content">
        <component :is="currentComponent"></component>
      </div>
    </div>
  </template>
  
  <script>
  import GlobalAlignment from './GlobalAlignment.vue';
  import VerificarCadenas from './VerificarCadenas.vue';
  import AlineamientoEstrella from './AlineamientoEstrella.vue';
  
  export default {
    data() {
      return {
        currentComponent: 'GlobalAlignment'
      };
    },
    components: {
      GlobalAlignment,
      VerificarCadenas,
      AlineamientoEstrella
    },
    methods: {
      navigateTo(component) {
        switch (component) {
          case 'global':
            this.currentComponent = 'GlobalAlignment';
            break;
          case 'verificar':
            this.currentComponent = 'VerificarCadenas';
            break;
          case 'estrella':
            this.currentComponent = 'AlineamientoEstrella';
            break;
          default:
            this.currentComponent = 'GlobalAlignment';
        }
      }
    }
  };
  </script>
  
  <style scoped>
  .container {
    font-family: Arial, sans-serif;
    text-align: center;
    margin: 0 auto;
    max-width: 800px;
    padding: 20px;
  }
  
  h1 {
    color: #333;
    margin-bottom: 20px;
  }
  
  .nav {
    list-style-type: none;
    padding: 0;
    display: flex;
    justify-content: center;
    gap: 20px;
    margin-bottom: 30px;
  }
  
  .nav li {
    cursor: pointer;
    padding: 10px 20px;
    border-radius: 5px;
    transition: background-color 0.3s;
  }
  
  .nav li:hover {
    background-color: #f0f0f0;
  }
  
  .nav li.active {
    background-color: #007bff;
    color: white;
  }
  
  .content {
    padding: 20px;
    border: 1px solid #ddd;
    border-radius: 5px;
  }
  </style>
  