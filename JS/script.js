window.onload = function(){

    document.getElementById('polynomialForm').addEventListener('submit', function(event) {
        event.preventDefault(); // Предотвращаем отправку формы по умолчанию
        const coefficients = document.getElementById('coefficients').value;

        // Отправляем запрос на сервер

        fetch(`http://localhost:3000/execute?string=${encodeURIComponent(coefficients)}`)
            .then(response => response.json())
            .then(data => {
                // Отображаем результат на странице
                let response = JSON.stringify(data);
                const lastIndex = response.lastIndexOf("n");
                const startIndex = response.lastIndexOf('"');
                response = response.substring(lastIndex + 1, startIndex);

                document.getElementById('result').innerText = response;
            })
            .catch(error => {
                console.error('Error:', error);
            });
    });
}
