const formColorSet = document.getElementById('form-color-set');
const buttonSwitchOffLeds = document.getElementById('switch-off-leds');

formColorSet.addEventListener('submit', formPost);
buttonSwitchOffLeds.addEventListener('click', buttonSwitch);

function formPost(event) {
    event.preventDefault();

    const color = document.getElementById('color-picker').value;
    const rgb = hexToRgb(color);

    if (rgb != null) {
        setColor(
            rgb.r,
            rgb.g,
            rgb.b
        );
    }
}

function buttonSwitch(event) {
    event.preventDefault();

    setColor(0, 0, 0)
}

function hexToRgb(hex) {
    const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16)
    } : null;
}

function setColor(r, g, b) {
    fetch('/led', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            'r': r,
            'g': g,
            'b': b
        })
    }).then(response => {
        console.log("Set color: " + response.ok);
    });
}

