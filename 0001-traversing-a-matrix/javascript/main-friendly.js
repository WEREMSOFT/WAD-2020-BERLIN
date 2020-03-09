const MATRIX_SIZE = 10000;
let arr = [];

for(let i = 0; i < MATRIX_SIZE; i++){
    arr[i] = [];
    for(let j = 0; j < MATRIX_SIZE; j++){
        arr[i][j] = Math.random();
    }
}

let result = 0;

beginTime = new Date();
for(let j = 0; j < MATRIX_SIZE; j++){
    for(let i = 0; i < MATRIX_SIZE; i++){
        result += arr[j][i] ;
    }
}
let endTime_row = new Date() - beginTime;

console.log('time by cache friendly: ', endTime_row);
return result;

