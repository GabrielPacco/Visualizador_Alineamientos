import js from '@eslint/js';
import pluginVue from 'eslint-plugin-vue';

export default [
  js.configs.recommended,
  ...pluginVue.configs['flat/essential'],
  {
    languageOptions: {
      globals: {
        console: 'readonly',
        FormData: 'readonly'
      }
    },
    rules: {}
  }
];
