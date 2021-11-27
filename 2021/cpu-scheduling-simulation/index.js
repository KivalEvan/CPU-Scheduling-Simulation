// process should start with 0
const procList = [];
let procCount = 0;
let procOffset = 1; // does not touch process value, only display offset it

const preset = {
    set_1: [{ process: 0, burstTime: 6, arrivalTime: 0, priority: 3 },
        { process: 1, burstTime: 4, arrivalTime: 1, priority: 3 },
        { process: 2, burstTime: 6, arrivalTime: 5, priority: 1 },
        { process: 3, burstTime: 6, arrivalTime: 6, priority: 1 },
        { process: 4, burstTime: 6, arrivalTime: 7, priority: 5 },
        { process: 5, burstTime: 6, arrivalTime: 8, priority: 6 }
    ],
    set_2: [{ process: 0, burstTime: 8, arrivalTime: 0, priority: 1 },
        { process: 5, burstTime: 6, arrivalTime: 0, priority: 1 },
        { process: 1, burstTime: 15, arrivalTime: 4, priority: 2 },
        { process: 4, burstTime: 13, arrivalTime: 9, priority: 2 },
        { process: 2, burstTime: 9, arrivalTime: 7, priority: 3 },
        { process: 3, burstTime: 5, arrivalTime: 13, priority: 3 }
    ],
    set_3: [{ process: 0, burstTime: 10, arrivalTime: 0, priority: 2 },
        { process: 1, burstTime: 2, arrivalTime: 3, priority: 4 },
        { process: 2, burstTime: 5, arrivalTime: 2, priority: 3 },
        { process: 3, burstTime: 7, arrivalTime: 3, priority: 1 },
        { process: 4, burstTime: 5, arrivalTime: 5, priority: 2 }
    ],
    set_4: [{ process: 2, burstTime: 2, arrivalTime: 4, priority: 1 },
        { process: 3, burstTime: 3, arrivalTime: 1, priority: 3 },
        { process: 4, burstTime: 1, arrivalTime: 3, priority: 2 },
        { process: 1, burstTime: 5, arrivalTime: 4, priority: 4 },
        { process: 0, burstTime: 4, arrivalTime: 0, priority: 1 }
    ],
    set_5: [{ process: 0, burstTime: 10, arrivalTime: 0, priority: 3 },
        { process: 1, burstTime: 1, arrivalTime: 3, priority: 1 },
        { process: 2, burstTime: 2, arrivalTime: 1, priority: 3 },
        { process: 3, burstTime: 1, arrivalTime: 5, priority: 4 },
        { process: 4, burstTime: 5, arrivalTime: 2, priority: 2 }
    ]
};

const input = {
    btime: false,
    atime: false,
    priority: false,
    add: false,
    fcfs: true,
    fcfsp: true,
    psjf: true,
    npsjf: true,
    pp: true,
    npp: true,
    rr: {
        enabled: true,
        quantum: 2
    },
    rrp: {
        enabled: true,
        quantum: 2
    },
    ganttChartScale: 1.5,
    halt: { // planned to have this feature to stop mid simulation but it's not needed, still functional
        enabled: false,
        time: 20
    }
}

// just to make rounding with decimal easier
function round(num, d = 0) {
    if (!d > 0) return Math.round(num);
    return Math.round(num * Math.pow(10, d)) / Math.pow(10, d);
}

function fcfs() {
    // deep copy instead so the original list isnt modified in any way somehow
    const proc = JSON.parse(JSON.stringify(procList));
    // for purpose to remember the initial burst time and to calculate waiting time
    for (let i = 0, len = proc.length; i < len; i++) {
        proc[i].OGBurstTime = proc[i].burstTime;
    }
    const result = {
        process: [],
        startTime: [],
        endTime: [],
        turnaroundTime: {},
        waitingTime: {}
    };
    const queue = [];
    let burst = null;

    for (let i = 0; (proc.length > 0 || queue.length > 0 || burst !== null) && !(input.halt.enabled && input.halt.time < i); i++) {
        // console.log('time', i)
        // push the process into queue by arrival time
        for (let j = 0, len = proc.length; j < len; j++) {
            if (proc[j].arrivalTime === i) {
                queue.push(proc[j]);
                proc.splice(j, 1);
                j--;
                len--;
            }
        }
        // pick the first that enters the queue
        if (burst === null && queue.length > 0) {
            burst = queue.shift();
            result.process.push(burst.process);
            result.startTime.push(i);
        }
        // do burst if exist
        if (burst !== null) {
            if (burst.burstTime > 0) {
                burst.burstTime--;
                if (burst.burstTime === 0) {
                    // because this is done on next time, +1 to current time
                    result.endTime.push(i+1);
                    result.turnaroundTime[burst.process] = i+1-burst.arrivalTime;
                    result.waitingTime[burst.process] = (i+1-burst.arrivalTime)-burst.OGBurstTime;
                    burst = null;
                }
            } else {
                // idk what happened if it ever happened
                // look for case that went negative burst time altho it shouldnt ever happen
                burst = null;
            }
        }
    }
    return result;
}
function fcfsp() {
    const proc = JSON.parse(JSON.stringify(procList));
    for (let i = 0, len = proc.length; i < len; i++) {
        proc[i].OGBurstTime = proc[i].burstTime;
    }
    const result = {
        process: [],
        startTime: [],
        endTime: [],
        turnaroundTime: {},
        waitingTime: {}
    };
    const queue = [];
    let burst = null;

    for (let i = 0; (proc.length > 0 || queue.length > 0 || burst !== null) && !(input.halt.enabled && input.halt.time < i); i++) {
        // console.log('time', i)
        for (let j = 0, len = proc.length; j < len; j++) {
            if (proc[j].arrivalTime === i) {
                queue.push(proc[j]);
                proc.splice(j, 1);
                j--;
                len--;
            }
        }
        let lowP = Number.MAX_SAFE_INTEGER;
        let index = -1;
        for (let q = 0, len = queue.length; q < len; q++) {
            if (queue[q].priority < lowP) {
                lowP = queue[q].priority;
                index = q;
            }
        }
        if (burst === null && index !== -1) {
            burst = queue[index];
            result.process.push(queue[index].process);
            result.startTime.push(i);
            queue.splice(index, 1);
        }
        if (burst !== null) {
            if (index !== -1 && burst.priority > lowP) {
                // put it to front of queue instead
                queue.unshift(burst);
                result.endTime.push(i);
                burst = queue[index+1];
                result.process.push(queue[index+1].process);
                result.startTime.push(i);
                queue.splice(index+1, 1);
            }
            if (burst.burstTime > 0) {
                burst.burstTime--;
                if (burst.burstTime === 0) {
                    result.endTime.push(i+1);
                    result.turnaroundTime[burst.process] = i+1-burst.arrivalTime;
                    result.waitingTime[burst.process] = (i+1-burst.arrivalTime)-burst.OGBurstTime;
                    burst = null;
                }
            } else {
                burst = null;
            }
        }
    }
    return result;
}
function psjf() {
    const proc = JSON.parse(JSON.stringify(procList));
    for (let i = 0, len = proc.length; i < len; i++) {
        proc[i].OGBurstTime = proc[i].burstTime;
    }
    const result = {
        process: [],
        startTime: [],
        endTime: [],
        turnaroundTime: {},
        waitingTime: {}
    };
    const queue = [];
    let burst = null;

    for (let i = 0; (proc.length > 0 || queue.length > 0 || burst !== null) && !(input.halt.enabled && input.halt.time < i); i++) {
        // console.log('time', i)
        for (let j = 0, len = proc.length; j < len; j++) {
            if (proc[j].arrivalTime === i) {
                queue.push(proc[j]);
                proc.splice(j, 1);
                j--;
                len--;
            }
        }
        let lowBT = Number.MAX_SAFE_INTEGER;
        let index = -1;
        for (let q = 0, len = queue.length; q < len; q++) {
            if (queue[q].burstTime < lowBT) {
                lowBT = queue[q].burstTime;
                index = q;
            }
        }
        if (burst === null && index !== -1) {
            if (index !== -1) {
                burst = queue[index];
                result.process.push(queue[index].process);
                result.startTime.push(i);
                queue.splice(index, 1);
            }
        }
        if (burst !== null) {
            if (index !== -1 && burst.burstTime > lowBT) {
                queue.push(burst);
                result.endTime.push(i);
                burst = queue[index];
                result.process.push(queue[index].process);
                result.startTime.push(i);
                queue.splice(index, 1);
            }
            if (burst.burstTime > 0) {
                burst.burstTime--;
                if (burst.burstTime === 0) {
                    result.endTime.push(i+1);
                    result.turnaroundTime[burst.process] = i+1-burst.arrivalTime;
                    result.waitingTime[burst.process] = (i+1-burst.arrivalTime)-burst.OGBurstTime;
                    burst = null;
                }
            } else {
                burst = null;
            }
        }
    }
    return result;
}
function npsjf() {
    const proc = JSON.parse(JSON.stringify(procList));
    for (let i = 0, len = proc.length; i < len; i++) {
        proc[i].OGBurstTime = proc[i].burstTime;
    }
    const result = {
        process: [],
        startTime: [],
        endTime: [],
        turnaroundTime: {},
        waitingTime: {}
    };
    const queue = [];
    let burst = null;

    for (let i = 0; (proc.length > 0 || queue.length > 0 || burst !== null) && !(input.halt.enabled && input.halt.time < i); i++) {
        // console.log('time', i)
        for (let j = 0, len = proc.length; j < len; j++) {
            if (proc[j].arrivalTime === i) {
                queue.push(proc[j]);
                proc.splice(j, 1);
                j--;
                len--;
            }
        }
        if (burst === null) {
            let lowBT = Number.MAX_SAFE_INTEGER;
            let index = -1;
            for (let q = 0, len = queue.length; q < len; q++) {
                if (queue[q].burstTime < lowBT) {
                    lowBT = queue[q].burstTime;
                    index = q;
                }
            }
            if (index !== -1) {
                burst = queue[index];
                result.process.push(queue[index].process);
                result.startTime.push(i);
                queue.splice(index, 1);
            }
        }
        if (burst !== null) {
            if (burst.burstTime > 0) {
                burst.burstTime--;
                if (burst.burstTime === 0) {
                    result.endTime.push(i+1);
                    result.turnaroundTime[burst.process] = i+1-burst.arrivalTime;
                    result.waitingTime[burst.process] = (i+1-burst.arrivalTime)-burst.OGBurstTime;
                    burst = null;
                }
            } else {
                burst = null;
            }
        }
    }
    return result;
}
function pp() {
    const proc = JSON.parse(JSON.stringify(procList));
    for (let i = 0, len = proc.length; i < len; i++) {
        proc[i].OGBurstTime = proc[i].burstTime;
    }
    const result = {
        process: [],
        startTime: [],
        endTime: [],
        turnaroundTime: {},
        waitingTime: {}
    };
    const queue = [];
    let burst = null;

    for (let i = 0; (proc.length > 0 || queue.length > 0 || burst !== null) && !(input.halt.enabled && input.halt.time < i); i++) {
        // console.log('time', i)
        for (let j = 0, len = proc.length; j < len; j++) {
            if (proc[j].arrivalTime === i) {
                queue.push(proc[j]);
                proc.splice(j, 1);
                j--;
                len--;
            }
        }
        let lowBT = Number.MAX_SAFE_INTEGER;
        let lowP = Number.MAX_SAFE_INTEGER;
        let index = -1;
        for (let q = 0, len = queue.length; q < len; q++) {
            if (queue[q].priority <= lowP) {
                if (queue[q].priority < lowP) {
                    lowBT = queue[q].burstTime;
                    lowP = queue[q].priority;
                    index = q;
                }
                else if (queue[q].burstTime < lowBT) {
                    lowBT = queue[q].burstTime;
                    lowP = queue[q].priority;
                    index = q;
                }
            }
        }
        if (burst === null && index !== -1) {
            burst = queue[index];
            result.process.push(queue[index].process);
            result.startTime.push(i);
            queue.splice(index, 1);
        }
        if (burst !== null) {
            if (burst.priority >= lowP) {
                if (burst.priority > lowP) {
                    queue.push(burst);
                    result.endTime.push(i);
                    burst = queue[index];
                    result.process.push(queue[index].process);
                    result.startTime.push(i);
                    queue.splice(index, 1);
                }
                else if (burst.burstTime > lowBT) {
                    queue.push(burst);
                    result.endTime.push(i);
                    burst = queue[index];
                    result.process.push(queue[index].process);
                    result.startTime.push(i);
                    queue.splice(index, 1);
                }
            }
            if (burst.burstTime > 0) {
                burst.burstTime--;
                if (burst.burstTime === 0) {
                    result.endTime.push(i+1);
                    result.turnaroundTime[burst.process] = i+1-burst.arrivalTime;
                    result.waitingTime[burst.process] = (i+1-burst.arrivalTime)-burst.OGBurstTime;
                    burst = null;
                }
            } else {
                burst = null;
            }
        }
    }
    return result;
}
function npp() {
    const proc = JSON.parse(JSON.stringify(procList));
    for (let i = 0, len = proc.length; i < len; i++) {
        proc[i].OGBurstTime = proc[i].burstTime;
    }
    const result = {
        process: [],
        startTime: [],
        endTime: [],
        turnaroundTime: {},
        waitingTime: {}
    };
    const queue = [];
    let burst = null;

    for (let i = 0; (proc.length > 0 || queue.length > 0 || burst !== null) && !(input.halt.enabled && input.halt.time < i); i++) {
        // console.log('time', i)
        for (let j = 0, len = proc.length; j < len; j++) {
            if (proc[j].arrivalTime === i) {
                queue.push(proc[j]);
                proc.splice(j, 1);
                j--;
                len--;
            }
        }
        if (burst === null) {
            let lowBT = Number.MAX_SAFE_INTEGER;
            let lowP = Number.MAX_SAFE_INTEGER;
            let index = -1;
            for (let q = 0, len = queue.length; q < len; q++) {
                if (queue[q].priority <= lowP) {
                    if (queue[q].priority < lowP) {
                        lowBT = queue[q].burstTime;
                        lowP = queue[q].priority;
                        index = q;
                    }
                    else if (queue[q].burstTime < lowBT) {
                        lowBT = queue[q].burstTime;
                        lowP = queue[q].priority;
                        index = q;
                    }
                }
            }
            if (index !== -1) {
                burst = queue[index];
                result.process.push(queue[index].process);
                result.startTime.push(i);
                queue.splice(index, 1);
            }
        }
        if (burst !== null) {
            if (burst.burstTime > 0) {
                burst.burstTime--;
                if (burst.burstTime === 0) {
                    result.endTime.push(i+1);
                    result.turnaroundTime[burst.process] = i+1-burst.arrivalTime;
                    result.waitingTime[burst.process] = (i+1-burst.arrivalTime)-burst.OGBurstTime;
                    burst = null;
                }
            } else {
                burst = null;
            }
        }
    }
    return result;
}
function rr() {
    const proc = JSON.parse(JSON.stringify(procList));
    for (let i = 0, len = proc.length; i < len; i++) {
        proc[i].OGBurstTime = proc[i].burstTime;
    }
    const result = {
        process: [],
        startTime: [],
        endTime: [],
        turnaroundTime: {},
        waitingTime: {}
    };
    const queue = [];
    let burst = null;
    let quanTime = 0;

    for (let i = 0; (proc.length > 0 || queue.length > 0 || burst !== null) && !(input.halt.enabled && input.halt.time < i); i++) {
        // console.log('time', i)
        for (let j = 0, len = proc.length; j < len; j++) {
            if (proc[j].arrivalTime === i) {
                queue.push(proc[j]);
                proc.splice(j, 1);
                j--;
                len--;
            }
        }
        if (burst !== null) {
            if (burst.burstTime > 0) {
                burst.burstTime--;
                quanTime--;
                if (burst.burstTime === 0) {
                    result.endTime.push(i);
                    result.turnaroundTime[burst.process] = i-burst.arrivalTime;
                    result.waitingTime[burst.process] = (i-burst.arrivalTime)-burst.OGBurstTime;
                    burst = null;
                }
                else if (quanTime === 0 && queue.length > 0) {
                    queue.push(burst);
                    result.endTime.push(i);
                    burst = null;
                }
            } else {
                burst = null;
            }
        }
        if (burst === null && queue.length > 0) {
            burst = queue.shift();
            quanTime = input.rr.quantum;
            result.process.push(burst.process);
            result.startTime.push(i);
        }
    }
    return result;
}
function rrp() {
    const proc = JSON.parse(JSON.stringify(procList));
    for (let i = 0, len = proc.length; i < len; i++) {
        proc[i].OGBurstTime = proc[i].burstTime;
    }
    const result = {
        process: [],
        startTime: [],
        endTime: [],
        turnaroundTime: {},
        waitingTime: {}
    };
    const queue = [];
    let burst = null;
    let quanTime = 0;

    for (let i = 0; (proc.length > 0 || queue.length > 0 || burst !== null) && !(input.halt.enabled && input.halt.time < i); i++) {
        // console.log('time', i)
        for (let j = 0, len = proc.length; j < len; j++) {
            if (proc[j].arrivalTime === i) {
                queue.push(proc[j]);
                proc.splice(j, 1);
                j--;
                len--;
            }
        }
        let lowP = Number.MAX_SAFE_INTEGER;
        let index = -1;
        for (let q = 0, len = queue.length; q < len; q++) {
            if (queue[q].priority < lowP) {
                lowP = queue[q].priority;
                index = q;
            }
        }
        if (burst === null && index !== -1 && queue.length > 0) {
            if (index !== -1) {
                burst = queue[index];
                quanTime = input.rrp.quantum;
                result.process.push(queue[index].process);
                result.startTime.push(i);
                queue.splice(index, 1);
            }
        }
        if (burst !== null) {
            if (burst.burstTime > 0) {
                burst.burstTime--;
                quanTime--;
                if (burst.burstTime === 0) {
                    result.endTime.push(i+1);
                    result.turnaroundTime[burst.process] = i+1-burst.arrivalTime;
                    result.waitingTime[burst.process] = (i+1-burst.arrivalTime)-burst.OGBurstTime;
                    burst = null;
                }
                else if (quanTime === 0 && burst.priority >= lowP) {
                    queue.push(burst);
                    result.endTime.push(i+1);
                    burst = null;
                }
            } else {
                burst = null;
            }
        }
    }
    return result;
}
// i would do Multilevel Queue Scheduling and Multilevel Feedback Queue Scheduling
// but i have no idea how to do that nor i know what to give for user input