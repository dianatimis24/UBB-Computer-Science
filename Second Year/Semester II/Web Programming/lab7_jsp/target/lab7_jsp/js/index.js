document.getElementById('loginForm').addEventListener('submit', function(event) {
    let ok = true;
    ['loginUser', 'loginPass'].forEach(function(id) {
        const input = document.getElementById(id);
        const error = document.getElementById(id + 'Err');
        if (!input.value.trim()) {
            error.textContent = 'This field is required.';
            input.classList.add('form__input--error');
            ok = false;
        } else {
            error.textContent = '';
            input.classList.remove('form__input--error');
        }
    });
    if (!ok) {
        event.preventDefault();
    }
});