const http = require('http');
const path = require('path');
const fs = require('fs');

const server = http.createServer((req,res) => {
    let filePath = path.join(__dirname, req.url === "/" ? "solidGrid.html" : req.url);

    let extName = path.extname(filePath);

    let contentType = "text/html";

    switch(extName){
        case ".js":
            contentType = "text/javascript";
            break;
        case ".css":
            contentType = "text/css";
            break;
    }

    if (contentType == "text/html" && extName == "") filePath += ".html";

    fs.readFile(filePath, (err, content) => {
        if (err) {
            //  Some server error
            res.writeHead(500);
            res.end(`Server Error: ${err.code}`);
        } else {
        // Success
        res.writeHead(200, { "Content-Type": contentType });
        res.end(content, "utf8");
        }
    });
});

const PORT = process.env.PORT || 5000;

server.listen(PORT, () => console.log(`Server running on ${PORT}`));