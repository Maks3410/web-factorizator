const express = require('express');
const bodyParser = require('body-parser');
const { exec } = require('child_process');
const path = require('path');
const polyPath = path.resolve(__dirname, 'poly.exe');

const app = express();
const PORT = process.env.PORT || 3000;

// Используем body-parser для обработки тела запроса в формате JSON
app.use(bodyParser.json());
const cors = require("cors");
app.use(cors());
// Обработчик GET запроса
app.get('/execute', (req, res) => {
    const inputString = req.query.string; // Получаем параметр 'string' из запроса

    if (!inputString) {
        return res.status(400).json({ error: 'Параметр "string" не предоставлен' });
    }

    inputString.replaceAll("%20", " ");
    console.log(inputString);
    // Запускаем внешнее приложение
    const command = `"${polyPath}" "${inputString}"`;



    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`Ошибка выполнения команды: ${error.message}`);
            return res.status(500).json({ error: 'Ошибка выполнения команды' });
        }
        if (stderr) {
            console.error(`Ошибка: ${stderr}`);
            return res.status(500).json({ error: 'Ошибка выполнения команды' });
        }

        // Отправляем результат выполнения команды как ответ на запрос
        res.status(200).json({ output: stdout.trim() });
    });
});

// Запуск сервера
app.listen(PORT, () => {
    console.log(`Сервер запущен на порту ${PORT}`);
});
