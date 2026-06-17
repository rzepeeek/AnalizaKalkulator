let chart = null;
let historyCounter = 0;

function setFunction(value) {
    document.getElementById("expression").value = value;
}

function addToFunction(value) {
    document.getElementById("expression").value += value;
}

function drawChart(expression) {
    const xValues = [];
    const yValues = [];

    // Generowanie punktów na wykresie
    for (let x = -5; x <= 5; x += 0.05) {
        const currentX = Math.round(x * 100) / 100;
        let y = null;

        if (expression === "x") {
            y = currentX;
        } else if (expression === "sin(x)") {
            y = Math.sin(currentX);
        } else if (expression === "cos(x)") {
            y = Math.cos(currentX);
        } else if (expression === "e^x") {
            y = Math.exp(currentX);
        } else if (expression === "ln(x)") {
            if (currentX > 0) y = Math.log(currentX);
        } else {
            const match = expression.match(/^x\^(\d+)$/);
            if (match) {
                const power = parseInt(match[1]);
                y = Math.pow(currentX, power);
            }
        }

        if (y !== null) {
            xValues.push(currentX);
            yValues.push(y);
        }
    }

    const ctx = document.getElementById("chart").getContext("2d");

    if (chart) chart.destroy();

    chart = new Chart(ctx, {
        type: "line",
        data: {
            labels: xValues,
            datasets: [
                {
                    label: expression,
                    data: yValues,
                    pointRadius: 0,
                    borderWidth: 3,
                    tension: 0.15,
                    borderColor: "rgba(54, 162, 235, 1)",
                    fill: false
                }
            ]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            scales: {
                x: {
                    type: 'category',
                    ticks: {
                        callback: function(val, index) {
                            return index % 10 === 0 ? this.getLabelForValue(val) : '';
                        }
                    }
                },
                y: {
                    beginAtZero: false
                }
            },
            plugins: {
                zoom: {
                    pan: {
                        enabled: true,
                        mode: "xy",
                        modifierKey: "shift",
                        threshold: 50
                    },
                    zoom: {
                        wheel: { enabled: true },
                        drag: { enabled: false },
                        pinch: { enabled: true },
                        mode: "xy"
                    }
                }
            }
        }
    });
}

async function calculate() {
    const expression = document.getElementById("expression").value;
    const expression2 = document.getElementById("expression2").value;
    const type = document.getElementById("type").value;
    const aVal = document.getElementById("a").value;
    const bVal = document.getElementById("b").value;

    const payload = expression + "|" + expression2 + "|" + type + "|" + aVal + "|" + bVal;

    const response = await fetch("http://localhost:8080/integral", {
        method: "POST",
        body: payload
    });

    const result = await response.text();
    document.getElementById("result").innerHTML = result;

    if (window.MathJax) {
        MathJax.typesetPromise();
    }

    let shortResult = "";
    if (type === "definite") {
        shortResult = `Granice: ${aVal} → ${bVal}`;
    } else {
        shortResult = "Obliczono";
    }

    const historyDiv = document.getElementById("history");
    let operationText = "";

    if (type === "definite") {
        operationText = `Całka oznaczona [${aVal}, ${bVal}]`;
    } else if (type === "derivative") {
        operationText = "Pochodna";
    } else {
        operationText = "Całka nieoznaczona";
    }

    historyCounter++;
    historyDiv.innerHTML = `
    <div class="history-item" onclick="setFunction('${expression}')">
        <small>#${historyCounter}</small>
        <b>${expression}</b>
        <span>${operationText}</span>
        <div class="history-result">${shortResult}</div>
    </div>
    ` + historyDiv.innerHTML;

    if (window.MathJax) {
        MathJax.typesetPromise();
    }

    // Wykres rysuje teraz wyłącznie samą linię funkcji, bez przekazywania granic
    drawChart(expression);
}

function clearHistory() {
    document.getElementById("history").innerHTML = "";
    historyCounter = 0;
}

const typeSelect = document.getElementById("type");

function updateBoundsVisibility() {
    const type = typeSelect.value;
    const displayBounds = (type === "definite" || type === "area_between" || type === "volume") ? "block" : "none";
    
    document.getElementById("a").style.display = displayBounds;
    document.getElementById("b").style.display = displayBounds;
    document.getElementById("expression2").style.display = (type === "area_between") ? "block" : "none";
}

typeSelect.addEventListener("change", updateBoundsVisibility);
updateBoundsVisibility();

function resetZoom() {
    if (chart) {
        chart.resetZoom();
    }
}

document.getElementById("chart").addEventListener("dblclick", () => {
    resetZoom();
});