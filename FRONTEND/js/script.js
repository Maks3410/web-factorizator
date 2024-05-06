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

                let firstChar = response.indexOf("n") + 1;
                let secondChar = response.indexOf("n", firstChar);
                let polynomial = response.substring(firstChar, secondChar - 1);
                let show = document.getElementById('show');
                if (!polynomial.includes("error")) {
                    show.style.display = "block";
                    let pol = document.getElementById("pol");
                    pol.innerText = polynomial;
                }
                else {
                    show.style.display = "none";
                }

                const lastIndex = response.lastIndexOf("n");
                const startIndex = response.lastIndexOf('"');
                response = response.substring(lastIndex + 1, startIndex);
                if (response.includes("не предоставлен")) {
                    response = "Неверный ввод";
                }

                document.getElementById('result').innerText = response;
            })
            .catch(error => {
                console.error('Error:', error);
            });
    });
}