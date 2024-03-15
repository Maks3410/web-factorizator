function validateInput(input) {
    var validCharacters = '0123456789xX^+-*.';  // Разрешенные символы
    var inputValue = input.value;
    var sanitizedInput = '';

    // Проверяем каждый символ во введенном значении
    for (var i = 0; i < inputValue.length; i++) {
        var currentChar = inputValue.charAt(i);

        // Если текущий символ разрешен, добавляем его в очищенную строку
        if (validCharacters.includes(currentChar)) {
            sanitizedInput += currentChar;
        }
    }

    input.value = sanitizedInput;
}

function calculatePolynomial() {
    var polynomialInput = document.getElementById('input-id').value;

    alert(polynomialInput);

    document.getElementById('result').innerHTML = "Введенный многочлен: " + '\n' + polynomialInput;
}