window.onload = function(){
    document.getElementById('polynomialForm').addEventListener('submit', function(event) {
        event.preventDefault(); // Предотвращаем отправку формы по умолчанию

        const degree = document.getElementById('degree').value;
        const coefficients = document.getElementById('coefficients').value;
        alert(coefficients);
        // Отправляем запрос на сервер

        fetch(`http://localhost:3000/execute?string=${coefficients}`)
            .then(response => response.json())
            .then(data => {
                // Отображаем результат на странице
                document.getElementById('result').innerText = JSON.stringify(data);
            })
            .catch(error => {
                console.error('Error:', error);
            });
    });
}
