// backend/server.js
const express = require('express');
const { exec } = require('child_process');
const multer = require('multer');
const path = require('path');
const app = express();
const port = 3000;

// Configuración de multer para manejar la subida de archivos
const upload = multer({ dest: 'uploads/' });

// Endpoint para subir archivos y ejecutar el código
app.post('/execute', upload.single('file'), (req, res) => {
  const file = req.file;
  const fileType = path.extname(file.originalname);

  let command = '';
  if (fileType === '.cpp') {
    command = `g++ ${file.path} -o ${file.path}.out && ${file.path}.out`;
  } else if (fileType === '.py') {
    command = `python ${file.path}`;
  }

  exec(command, (error, stdout, stderr) => {
    if (error) {
      res.status(500).send({ error: stderr });
      return;
    }
    res.send({ output: stdout });
  });
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
