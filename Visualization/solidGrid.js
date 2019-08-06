let ordemGrid = 7;
let r = 10;
let selectedVertex = [];

let canvas;
let ctx;
let rect;

function draw(){
    canvas = document.getElementById("canvas");
    ctx = canvas.getContext('2d');
    rect = canvas.getBoundingClientRect();
    canvas.addEventListener('mousedown',onClick,false);

    for(let i=0; i<ordemGrid;i++){
        for(let j=0;j<ordemGrid;j++){
            ctx.beginPath();

            let x = 20 + j*80;
            let y = 20 + i*80;

            var raio = r;

            ctx.arc(x, y, raio, 0, 2 * Math.PI, true);
            ctx.stroke();
        }
    }
}

function refresh(){
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    for(let i=0; i<ordemGrid;i++){
        for(let j=0;j<ordemGrid;j++){
            ctx.beginPath();

            let x = 20 + j*80;
            let y = 20 + i*80;

            var raio = r;

            ctx.arc(x, y, raio, 0, 2 * Math.PI, true);
            
            if( selectedVertex.includes(i*ordemGrid + j) ){
                ctx.fill();
            }else{
                ctx.stroke();
            } 
        }
    }
}

function dist(x1,y1,x2,y2) {
    return Math.sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

function onClick(event){
    let cx = event.clientX - rect.left;
    let cy = event.clientY - rect.top;

    console.log('Coordinates',cx,cy);

    for(let i=0; i<ordemGrid;i++){
        for(let j=0;j<ordemGrid;j++){
            ctx.beginPath();

            let x = 20 + j*80;
            let y = 20 + i*80;

            let d = dist(x,y,cx,cy);

            console.log('Circle: ',i*ordemGrid+j,x,y);
            console.log('info:',d);

            if( d < r ){
                if( selectedVertex.includes(i*ordemGrid + j) ){
                    let index = selectedVertex.indexOf(i*ordemGrid + j);
                    selectedVertex.splice(index, 1);
                }else{
                    selectedVertex.push(i*ordemGrid + j);
                }
                refresh();
                break;
            }
        }
    }
    console.log('Click', selectedVertex );
}