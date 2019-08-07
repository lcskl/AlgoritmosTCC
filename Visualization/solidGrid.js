let ordemGrid = 7;
let r = 10;
let selectedVertex = [];
let selectedEdge_H = [];
let selectedEdge_V = [];

let canvas;
let ctx;
let rect;

function draw(){
    canvas = document.getElementById("canvas");
    ctx = canvas.getContext('2d');
    rect = canvas.getBoundingClientRect();
    canvas.addEventListener('mousedown',onClick,false);
    canvas.addEventListener('mousemove',onHover,false);

    //Desenhando Vértices
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

    //Desenhando vértices
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

    //Desenhando Arestas
    for(let i=0; i<ordemGrid;i++){
        for(let j=0;j<ordemGrid;j++){
            ctx.beginPath();

            //Aresta horizontal
            if(j < ordemGrid - 1){
                if( selectedEdge_H.includes(i*ordemGrid + j) ){
                    let x1 = 20 + j*80;
                    let y1 = 20 + i*80;
                    let x2 = 20 + (j+1)*80;

                    ctx.strokeRect(x1+r,y1-1,x2-x1-2*r,2);
                }
            }

            //Aresta vertical
            if(i < ordemGrid - 1){
                if( selectedEdge_V.includes(i*ordemGrid + j) ){
                    let x1 = 20 + j*80;
                    let y1 = 20 + i*80;
                    let y2 = 20 + (i+1)*80; 

                ctx.strokeRect(x1-1,y1+r,2,y2-y1-2*r);
                }
            }
        }
    }
}

function dist(x1,y1,x2,y2) {
    return Math.sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

function inVertex(i,j,cx,cy){
    let x = 20 + j*80;
    let y = 20 + i*80;

    let d = dist(x,y,cx,cy);

    if( d < r ){
        if( selectedVertex.includes(i*ordemGrid + j) ){
            let index = selectedVertex.indexOf(i*ordemGrid + j);
            selectedVertex.splice(index, 1);
        }else{
            selectedVertex.push(i*ordemGrid + j);
        }
        return true;
    }
    return false;
}

function printDashedLine(x1,y1,x2,y2){
    ctx.save();
    ctx.setLineDash([5,3]);
    ctx.beginPath();
    ctx.moveTo(x1,y1);
    ctx.lineTo(x2,y2);
    ctx.stroke();
    ctx.restore();
}

function inEdge(i,j,cx,cy, add = false){
    let x1 = 20 + j*80;
    let y1 = 20 + i*80;

    //Aresta Horizontal
    if( j < ordemGrid - 1){
        let x2 = x1 + 80;
        if( cx > x1 + r && cx < x2 - r && cy > y1 - r && cy < y1 + r){
            if(add){
                if( selectedEdge_H.includes(i*ordemGrid + j) ){
                    let index = selectedEdge_H.indexOf(i*ordemGrid + j);
                    selectedEdge_H.splice(index, 1);
                }else{
                    selectedEdge_H.push(i*ordemGrid + j);
                }
            }else{
                printDashedLine(x1+r,y1,x2-r,y1);
            }
            return true;
        }
    }

    //Aresta Vertical
    if( i < ordemGrid - 1){
        let y2 = y1 + 80;
        if( cx > x1-r && cx < x1+r && cy > y1+r && cy < y2-r){
            if(add){
                if( selectedEdge_V.includes(i*ordemGrid + j) ){
                    let index = selectedEdge_V.indexOf(i*ordemGrid + j);
                    selectedEdge_V.splice(index, 1);
                }else{
                    selectedEdge_V.push(i*ordemGrid + j);
                }
            }else{
                printDashedLine(x1,y1+r,x1,y2-r);
            }
            return true;
        }
    }

    return false;
}

function onClick(event){
    let cx = event.clientX - rect.left;
    let cy = event.clientY - rect.top;

    console.log('Coordinates',cx,cy);

    for(let i=0; i<ordemGrid;i++){
        for(let j=0;j<ordemGrid;j++){

            if( inVertex(i,j,cx,cy) || inEdge(i,j,cx,cy,true)){
                refresh();
                break;
            }
        }
    }
    console.log('Click', selectedVertex );
}

function onHover(event){
    let cx = event.clientX - rect.left;
    let cy = event.clientY - rect.top;

    console.log("Mouse pos: ",cx,cy);

    let overSomeEdge = false;

    for(let i=0; i<ordemGrid;i++){
        for(let j=0;j<ordemGrid;j++){

            if( inEdge(i,j,cx,cy) ){
                console.log("DENTRO");
                overSomeEdge = true;
                break;
            }
        }
    }

    if( overSomeEdge === false){
        refresh();
    }
}