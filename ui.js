$('#input-process').val(`P${procCount + procOffset}`);
if (input.fcfs) $('#input-fcfs').prop('checked', true);
if (input.fcfsp) $('#input-fcfsp').prop('checked', true);
if (input.psjf) $('#input-psjf').prop('checked', true);
if (input.npsjf) $('#input-npsjf').prop('checked', true);
if (input.pp) $('#input-pp').prop('checked', true);
if (input.npp) $('#input-npp').prop('checked', true);
if (input.rr.enabled) $('#input-rr').prop('checked', true);
if (input.rrp.enabled) $('#input-rrp').prop('checked', true);
$('#input-rr-quantum').val(input.rr.quantum);
$('#input-rrp-quantum').val(input.rrp.quantum);
if (procCount === 0) {
    $('#input-remove').prop('disabled', true);
    $('#input-simulate').prop('disabled', true);
}
updateTable();

$('#input-offset-add').click(function() {
    procOffset++;
    $('#input-process').val(`P${procCount + procOffset}`);
    updateTable();
});
$('#input-offset-sub').click(function() {
    if (procOffset > 0) {
        procOffset--;
        $('#input-process').val(`P${procCount + procOffset}`);
        updateTable();
    }
});
$('#input-btime').change(function() {
    input.btime = true;
    $('#input-btime').val(this.value > 0 ? Math.ceil(this.value) : 1);
    if (!input.add) checkAddProcess();
});
$('#input-atime').change(function() {
    input.atime = true;
    $('#input-atime').val(this.value >= 0 ? Math.ceil(this.value) : 0);
    if (!input.add) checkAddProcess();
});
$('#input-priority').change(function() {
    input.priority = true;
    $('#input-priority').val(this.value > 0 ? Math.ceil(this.value) : 1);
    if (!input.add) checkAddProcess();
});
$('#input-add').click(function() {
    procList.push({ 
        process: procCount,
        burstTime: parseInt($('#input-btime').val()),
        arrivalTime: parseInt($('#input-atime').val()),
        priority: parseInt($('#input-priority').val())
    });
    if (procCount === 0) {
        $('#input-remove').prop('disabled', false);
        $('#input-simulate').prop('disabled', false);
    }
    procCount += 1;
    $('#input-process').val(`P${procCount + procOffset}`);
    resetAddProcess();
    updateTable();
});
$('#input-remove').click(function() {
    if (procList.length > 0) {
        procList.pop()
        procCount -= 1;
        if (procCount === 0) {
            $('#input-remove').prop('disabled', true);
            $('#input-simulate').prop('disabled', true);
        }
        $('#input-process').val(`P${procCount + procOffset}`);
        updateTable();
    }
});
$('#input-reset').click(function() {
    procList.splice(0, procList.length);
    procCount = 0;
    if (procCount === 0) {
        $('#input-remove').prop('disabled', true);
        $('#input-simulate').prop('disabled', true);
    }
    $('#input-process').val(`P${procCount + procOffset}`);
    updateTable();
});
// dont mind the spaghetti code
$('#input-preset-1').click(function() {
    procList.splice(0, procList.length);
    for (let i = 0, len = preset.set_1.length; i < len; i++) {
        procList.push(preset.set_1[i]);
    }
    procCount = procList.length;
    $('#input-remove').prop('disabled', false);
    $('#input-simulate').prop('disabled', false);
    $('#input-process').val(`P${procCount + procOffset}`);
    updateTable();
});
$('#input-preset-2').click(function() {
    procList.splice(0, procList.length);
    for (let i = 0, len = preset.set_2.length; i < len; i++) {
        procList.push(preset.set_2[i]);
    }
    procCount = procList.length;
    $('#input-remove').prop('disabled', false);
    $('#input-simulate').prop('disabled', false);
    $('#input-process').val(`P${procCount + procOffset}`);
    updateTable();
});
$('#input-preset-3').click(function() {
    procList.splice(0, procList.length);
    for (let i = 0, len = preset.set_3.length; i < len; i++) {
        procList.push(preset.set_3[i]);
    }
    procCount = procList.length;
    $('#input-remove').prop('disabled', false);
    $('#input-simulate').prop('disabled', false);
    $('#input-process').val(`P${procCount + procOffset}`);
    updateTable();
});
$('#input-preset-4').click(function() {
    procList.splice(0, procList.length);
    for (let i = 0, len = preset.set_4.length; i < len; i++) {
        procList.push(preset.set_4[i]);
    }
    procCount = procList.length;
    $('#input-remove').prop('disabled', false);
    $('#input-simulate').prop('disabled', false);
    $('#input-process').val(`P${procCount + procOffset}`);
    updateTable();
});
$('#input-preset-5').click(function() {
    procList.splice(0, procList.length);
    for (let i = 0, len = preset.set_5.length; i < len; i++) {
        procList.push(preset.set_5[i]);
    }
    procCount = procList.length;
    $('#input-remove').prop('disabled', false);
    $('#input-simulate').prop('disabled', false);
    $('#input-process').val(`P${procCount + procOffset}`);
    updateTable();
});

$('#input-fcfs').click(function() {
    if ($(this).prop('checked')) {
        input.fcfs = true;
    } else {
        input.fcfs = false;
    }
});
$('#input-psjf').click(function() {
    if ($(this).prop('checked')) {
        input.psjf = true;
    } else {
        input.psjf = false;
    }
});
$('#input-npsjf').click(function() {
    if ($(this).prop('checked')) {
        input.npsjf = true;
    } else {
        input.npsjf = false;
    }
});
$('#input-rr').click(function() {
    if ($(this).prop('checked')) {
        input.rr.enabled = true;
    } else {
        input.rr.enabled = false;
    }
});
$('#input-rr-quantum').change(function() {
    input.rr.quantum = this.value > 0 ? Math.ceil(this.value) : 1;
    $('#input-rr-quantum').val(input.rr.quantum);
});
$('#input-fcfsp').click(function() {
    if ($(this).prop('checked')) {
        input.fcfsp = true;
    } else {
        input.fcfsp = false;
    }
});
$('#input-pp').click(function() {
    if ($(this).prop('checked')) {
        input.pp = true;
    } else {
        input.pp = false;
    }
});
$('#input-npp').click(function() {
    if ($(this).prop('checked')) {
        input.npp = true;
    } else {
        input.npp = false;
    }
});
$('#input-rrp').click(function() {
    if ($(this).prop('checked')) {
        input.rrp.enabled = true;
    } else {
        input.rrp.enabled = false;
    }
});
$('#input-rrp-quantum').change(function() {
    input.rrp.quantum = this.value > 0 ? Math.ceil(this.value) : 1;
    $('#input-rrp-quantum').val(input.rrp.quantum);
});

$('#input-simulate').click(function() {
    if (procList.length > 0) {
        simulate();
    }
});

// look at this spaghetti code
function simulate() {
    // debugging purpose
    console.log(procList);
    // empty this output html
    $('.output').empty();
    if (input.fcfs) {
        console.log('simulating fcfs');
        let result = fcfs();
        let header = $('<span>', {
            class: 'output-header',
            text: 'First-Come First-Served'
        });
        let chart = drawGanttChart(result);
        let tTime = createTableProcess(result.turnaroundTime, 'Turnaround Time');
        let wTime = createTableProcess(result.waitingTime, 'Waiting Time');
        let col1 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(tTime);
        let col2 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(wTime);
        let main = $('<div>', {
            width: '100%'
        })
        .append(col1)
        .append(col2);
        let group = $('<div>', {
            id: 'fcfs'
        })
        .append(header)
        .append(chart)
        .append(main)
        .append($('<br>'))
        .append($('<hr>'));

        $('.output').append(group);
    }
    if (input.fcfsp) {
        console.log('simulating fcfsp');
        let result = fcfsp();
        let header = $('<span>', {
            class: 'output-header',
            text: 'First-Come First-Served with Priority'
        });
        let chart = drawGanttChart(result);
        let tTime = createTableProcess(result.turnaroundTime, 'Turnaround Time');
        let wTime = createTableProcess(result.waitingTime, 'Waiting Time');
        let col1 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(tTime);
        let col2 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(wTime);
        let main = $('<div>', {
            width: '100%'
        })
        .append(col1)
        .append(col2);
        let group = $('<div>', {
            id: 'fcfsp'
        })
        .append(header)
        .append(chart)
        .append(main)
        .append($('<br>'))
        .append($('<hr>'));

        $('.output').append(group);
    }
    if (input.psjf) {
        console.log('simulating psjf');
        let result = psjf();
        let header = $('<span>', {
            class: 'output-header',
            text: 'Preemptive Shortest-Job-First'
        });
        let chart = drawGanttChart(result);
        let tTime = createTableProcess(result.turnaroundTime, 'Turnaround Time');
        let wTime = createTableProcess(result.waitingTime, 'Waiting Time');
        let col1 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(tTime);
        let col2 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(wTime);
        let main = $('<div>', {
            width: '100%'
        })
        .append(col1)
        .append(col2);
        let group = $('<div>', {
            id: 'psjf'
        })
        .append(header)
        .append(chart)
        .append(main)
        .append($('<br>'))
        .append($('<hr>'));

        $('.output').append(group);
    }
    if (input.npsjf) {
        console.log('simulating npsjf');
        let result = npsjf();
        let header = $('<span>', {
            class: 'output-header',
            text: 'Non-preemptive Shortest-Job-First'
        });
        let chart = drawGanttChart(result);
        let tTime = createTableProcess(result.turnaroundTime, 'Turnaround Time');
        let wTime = createTableProcess(result.waitingTime, 'Waiting Time');
        let col1 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(tTime);
        let col2 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(wTime);
        let main = $('<div>', {
            width: '100%'
        })
        .append(col1)
        .append(col2);
        let group = $('<div>', {
            id: 'npsjf'
        })
        .append(header)
        .append(chart)
        .append(main)
        .append($('<br>'))
        .append($('<hr>'));

        $('.output').append(group);
    }
    if (input.pp) {
        console.log('simulating pp');
        let result = pp();
        let header = $('<span>', {
            class: 'output-header',
            text: 'Preemptive Priority'
        });
        let chart = drawGanttChart(result);
        let tTime = createTableProcess(result.turnaroundTime, 'Turnaround Time');
        let wTime = createTableProcess(result.waitingTime, 'Waiting Time');
        let col1 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(tTime);
        let col2 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(wTime);
        let main = $('<div>', {
            width: '100%'
        })
        .append(col1)
        .append(col2);
        let group = $('<div>', {
            id: 'pp'
        })
        .append(header)
        .append(chart)
        .append(main)
        .append($('<br>'))
        .append($('<hr>'));

        $('.output').append(group);
    }
    if (input.npp) {
        console.log('simulating npp');
        let result = npp();
        let header = $('<span>', {
            class: 'output-header',
            text: 'Non-preemptive Priority'
        });
        let chart = drawGanttChart(result);
        let tTime = createTableProcess(result.turnaroundTime, 'Turnaround Time');
        let wTime = createTableProcess(result.waitingTime, 'Waiting Time');
        let col1 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(tTime);
        let col2 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(wTime);
        let main = $('<div>', {
            width: '100%'
        })
        .append(col1)
        .append(col2);
        let group = $('<div>', {
            id: 'npp'
        })
        .append(header)
        .append(chart)
        .append(main)
        .append($('<br>'))
        .append($('<hr>'));

        $('.output').append(group);
    }
    if (input.rr.enabled) {
        console.log('simulating rr');
        let result = rr();
        let header = $('<span>', {
            class: 'output-header',
            text: `Round Robin (quantum = ${input.rr.quantum})`
        });
        let chart = drawGanttChart(result);
        let tTime = createTableProcess(result.turnaroundTime, 'Turnaround Time');
        let wTime = createTableProcess(result.waitingTime, 'Waiting Time');
        let col1 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(tTime);
        let col2 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(wTime);
        let main = $('<div>', {
            width: '100%'
        })
        .append(col1)
        .append(col2);
        let group = $('<div>', {
            id: 'rr'
        })
        .append(header)
        .append(chart)
        .append(main)
        .append($('<br>'))
        .append($('<hr>'));

        $('.output').append(group);
    }
    if (input.rrp.enabled) {
        console.log('simulating rrp');
        let result = rrp();
        let header = $('<span>', {
            class: 'output-header',
            text: `Round Robin with Priority (quantum = ${input.rrp.quantum})`
        });
        let chart = drawGanttChart(result);
        let tTime = createTableProcess(result.turnaroundTime, 'Turnaround Time');
        let wTime = createTableProcess(result.waitingTime, 'Waiting Time');
        let col1 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(tTime);
        let col2 = $('<div>', {
            css: {
                display: 'inline-block',
                width: '50%'
            }
        }).append(wTime);
        let main = $('<div>', {
            width: '100%'
        })
        .append(col1)
        .append(col2);
        let group = $('<div>', {
            id: 'rrp'
        })
        .append(header)
        .append(chart)
        .append(main)
        .append($('<br>'))
        .append($('<hr>'));

        $('.output').append(group);
    }
}
function drawGanttChart(data) {
    // im too lazy to make table so have pseudotable instead
    let table = $('<div>', {class: 'table'});
    for (let i = 0, len = data.process.length; i < len; i++) {
        let process = $('<div>', {
            class: 'table-content',
            css: {
                'border': '1px solid white'
            },
            text: `P${data.process[i] + procOffset}`
        });
        let time = $('<div>', {
            class: 'table-content',
            text: data.startTime[i]
        });
        let element = $('<div>', {
            class: 'table-element',
            width: `${(data.endTime[i]-data.startTime[i])*input.ganttChartScale}em`
        })
        .append(process)
        .append(time);

        table.append(element);

        // check if next process in list has gap or end of schedule
        if (data.endTime[i] !== data.startTime[i+1]) {
            process = $('<div>', {
                class: 'table-content',
                text: '|',
                css: {
                    'color': '#171717' // casually hiding text the same as background
                }
            });
            time = $('<div>', {
                class: 'table-content',
                text: data.endTime[i]
            });
            element = $('<div>', {
                class: 'table-element',
                width: data.startTime[i+1] !== undefined ? `${(data.startTime[i+1]-data.endTime[i])*input.ganttChartScale}em` : ''
            })
            .append(process)
            .append(time);
            table.append(element);
        }
    }
    return table;
}
function createTableProcess(data, text) {
    // ok for real i dont know how to make table with jquery
    let total = 0;
    let length = 0;
    let header1 = $('<div>', {
        class: 'table-content',
        css: {
            'border-bottom': '1px solid white'
        },
        text: 'Process'
    })
    let header2 = $('<div>', {
        class: 'table-content',
        css: {
            'border-bottom': '1px solid white'
        },
        text: text
    })
    let column1 = $('<div>', {
        class: 'table-element',
        width: '6em',
        css: {
            'border': '1px solid white'
        }
    })
    .append(header1);
    let column2 = $('<div>', {
        class: 'table-element',
        width: '12em',
        css: {
            'border': '1px solid white'
        }
    })
    .append(header2);
    for (const p in data) {
        let process = $('<div>', {
            class: 'table-content',
            text: `P${parseInt(p) + procOffset}`
        });
        let time = $('<div>', {
            class: 'table-content',
            text: data[p]
        });
        column1.append(process);
        column2.append(time);
        total += data[p];
        length++;
    }
    let table = $('<div>')
    .append(column1)
    .append(column2);

    let avg = $('<span>', {
        html: `Total ${text}: ${total}ms<br>Average ${text}: ${length > 0 ? round(total/length, 3) : 0}ms`
    });

    let group = $('<div>')
    .append(table)
    .append(avg);
    return group;
}

function resetAddProcess() {
    $('#input-btime').val('');
    $('#input-atime').val('');
    $('#input-priority').val('');
    input.btime = false;
    input.atime = false;
    input.priority = false;
    checkAddProcess();
}

function checkAddProcess() {
    if (input.btime && input.atime && input.priority) {
        $('#input-add').prop('disabled', false);
        input.add = true;
    } else {
        $('#input-add').prop('disabled', true);
        input.add = false;
    }
}

function updateTable() {
    // default show this for empty list
    if (!procList.length > 0) {
        $('#process').html('-');
        $('#btime').html('-');
        $('#atime').html('-');
        $('#priority').html('-');
        return;
    }

    // also sort array for the input for readability because who the hell randomise process position
    procList.sort((a, b) => a.process-b.process);
    $('#process').html(procList.map(list => `P${list.process + procOffset}`).join('<br>'));
    $('#btime').html(procList.map(list => list.burstTime).join('<br>'));
    $('#atime').html(procList.map(list => list.arrivalTime).join('<br>'));
    $('#priority').html(procList.map(list => list.priority).join('<br>'));
}