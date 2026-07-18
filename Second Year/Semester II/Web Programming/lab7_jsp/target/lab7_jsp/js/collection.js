function openModal(id) { document.getElementById(id).classList.add('modal--open'); }
function closeModal(id) { document.getElementById(id).classList.remove('modal--open'); }

document.addEventListener('keydown', function(keyboardEvent) {
    if (keyboardEvent.key === 'Escape') {
        document.querySelectorAll('.modal--open').forEach(function(element) {
            element.classList.remove('modal--open');
        });
    }
});

function confirmDelete(event, id) {
    event.stopPropagation();
    if (!confirm('Delete this URL?')) {
        return;
    }
    fetch('UrlController?id=' + id, {
        method: 'DELETE'
    }).then(function() {
        window.location.reload();
    });
}

document.getElementById('addForm').addEventListener('submit', function(event) {
    const value = document.getElementById('addUrl').value.trim();
    const error = document.getElementById('addUrlErr');
    if (!value) {
        error.textContent = 'Required.';
        event.preventDefault();
        return;
    }
    if (!value.match(/^https?:\/\/.+/)) {
        error.textContent = 'Must start with http:// or https://';
        event.preventDefault();
        return;
    }
    error.textContent = '';
});

let topNTimeout;
document.getElementById('topNInput').addEventListener('input', function() {
    clearTimeout(topNTimeout);
    topNTimeout = setTimeout(function() {
        document.getElementById('topNInput').form.submit();
    }, 600);
});