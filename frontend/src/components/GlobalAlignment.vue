<template>
    <div>
      <h2>Alineamiento Global</h2>
      <form @submit.prevent="submitAlignment">
        <div>
          <label for="seq1">Secuencia 1:</label>
          <input type="text" id="seq1" v-model="seq1" required>
        </div>
        <div>
          <label for="seq2">Secuencia 2:</label>
          <input type="text" id="seq2" v-model="seq2" required>
        </div>
        <button type="submit">Ejecutar Alineamiento</button>
      </form>
      <div v-if="output">
        <h3>Resultados:</h3>
        <pre>{{ output }}</pre>
      </div>
    </div>
  </template>
  
  <script>
  import axios from 'axios';
  
  export default {
    data() {
      return {
        seq1: '',
        seq2: '',
        output: ''
      };
    },
    methods: {
      async submitAlignment() {
        try {
          const formData = new FormData();
          formData.append('seq1', this.seq1);
          formData.append('seq2', this.seq2);
          
          const response = await axios.post('http://localhost:3000/execute-cpp', formData, {
            headers: {
              'Content-Type': 'application/json'
            }
          });
          
          this.output = response.data.output;
        } catch (error) {
          console.error('Error ejecutando el alineamiento:', error);
        }
      }
    }
  };
  </script>
  
  <style scoped>
  form {
    margin-bottom: 20px;
  }
  
  label {
    display: block;
    margin-top: 10px;
  }
  
  button {
    margin-top: 10px;
  }
  </style>
  