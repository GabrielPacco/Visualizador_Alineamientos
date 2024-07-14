const express = require('express');
const { exec } = require('child_process');
const multer = require('multer');
const path = require('path');
const fs = require('fs');
const app = express();
const port = 3000;

const upload = multer({ dest: 'uploads/' });

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.post('/execute-cpp', (req, res) => {
  const seq1 = req.body.seq1;
  const seq2 = req.body.seq2;
  
  const scriptPath = path.join(__dirname, 'compile_and_run_cpp.bat');
  const resultFilePath = path.join(__dirname, 'cpp', 'alineamiento_global', 'alignment_results.txt');

  // Ejecutar el script de compilación y ejecución
  exec(`"${scriptPath}" ${seq1} ${seq2}`, (error, stdout, stderr) => {
    if (error) {
      console.error(`Error ejecutando el script: ${error}`);
      return res.status(500).send({ error: stderr });
    }
    
    // Leer el archivo de resultados
    fs.readFile(resultFilePath, 'utf8', (err, data) => {
      if (err) {
        console.error(`Error leyendo el archivo de resultados: ${err}`);
        return res.status(500).send({ error: err.message });
      }
      
      // Enviar el contenido del archivo de resultados al cliente
      res.send({ output: data });
    });
  });
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
