const { query } = require("express");
const express = require("express");
const https = require("https");
const bodyParser = require("body-parser");
const app = express();

app.use(bodyParser.urlencoded({extended: true}));

app.get("/",function(req,res){
   res.sendFile(__dirname + "/index.html");
// res.send("hello we are begining with api");
});
app.post("/",function(req,res){
    console.log("post request received");
    const query = req.body.cityName;
const apiKey = "5bceaf9b4ea746792bbcc1c2675ec4de";
const url="https:api.openweathermap.org/data/2.5/weather?q="+query+"&appid="+ apiKey+"";
https.get(url,function(response){
    console.log(response.statusCode);

    response.on("data",function(data){
        console.log(data);
        const weatherData=JSON.parse(data);
        console.log(weatherData);
        const pressure = weatherData.main.pressure;
        console.log(pressure);
        const temperature = weatherData.main.temp;
        console.log(temperature);
        const des = weatherData.weather[0].description;
        console.log(des);
        res.write("<h1>The weather is currently " +des +"</h1>")
        res.write("<h1> The Temperature is:"+temperature+ "degree fahareinheit</h1>");
        res.write("<h1>The pressure in "+query+" is " + pressure+ "</h1>")
        res.send
    })
});

})


app.listen(3000,function(){
    console.log("Server started at port 3000");
});