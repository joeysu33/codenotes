function getData() {
    var i,j,cnt;
    var mx = []
    cnt=0;
    for(i=0; i<10; ++i) {
        mx[i] = []
        for(j=0; j<10; ++j) {
            mx[i][j] = cnt++;
        }
    }
    return mx;
}

function getData2() {
    var mx =[1,2,null, undefined]
    return mx;
}

function computeSum(matrix) {
    var sum = 0, success = false;
    compute_sum:
    if(matrix) {
        for(var x=0; x<matrix.length; ++x) {
            var row = matrix[x];
            if(!row) break compute_sum;
            for(var y=0; y<row.length; ++y) {
                var cell = row[y];
                if(isNaN(cell)) break compute_sum;
                sum += cell;
            }
        }
        success = true;
    }

    if(success) {
        console.log("sum="+sum)
    } else {
        console.log("break label");
    }
}

computeSum(getData());
computeSum([]);
computeSum(getData2());




