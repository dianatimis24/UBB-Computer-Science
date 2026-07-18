const items = Array.from(document.querySelectorAll('.gallery__item')).slice(1);
// const items = document.querySelectorAll('.gallery__item'); 
// - initial, before the required modification (1st not be exposed)
const fullImage = document.getElementById('fullImage');
const hint = document.querySelector('.gallery__hint');

function showFullImage(item) {
    const newSource = item.dataset.full;
    const newAlt = item.querySelector('.gallery__thumb').alt;

    document.querySelectorAll('.gallery__item--active').forEach(el => {
        el.classList.remove('gallery__item--active');
        el.querySelector('.gallery__thumb').classList.remove('gallery__thumb--active');
    });

    item.classList.add('gallery__item--active');
    item.querySelector('.gallery__thumb').classList.add('gallery__thumb--active');

    hint.style.opacity = '0';

    fullImage.classList.remove('gallery__full--visible');

    setTimeout(() => {
        fullImage.src = newSource;
        fullImage.alt = newAlt;
        fullImage.onload = () => fullImage.classList.add('gallery__full--visible');
        if (fullImage.complete) {
            fullImage.classList.add('gallery__full--visible');
        }
    }, 200);
}

items.forEach(item => {
    item.addEventListener('mouseenter', () => showFullImage(item));
});