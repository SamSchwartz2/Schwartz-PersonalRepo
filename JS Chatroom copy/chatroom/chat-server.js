// Require the packages we will use:
const http = require("http"),
    fs = require("fs");

const port = 3456;
const file = "client.html";
// Listen for HTTP connections.  This is essentially a miniature static file server that only serves our one file, client.html, on port 3456:
const server = http.createServer(function (req, res) {
    // This callback runs when a new connection is made to our HTTP server.
    fs.readFile(file, function (err, data) {
        // This callback runs when the client.html file has been read from the filesystem.

        if (err) return res.writeHead(500);
        res.writeHead(200);
        res.end(data);
    });
});
server.listen(port);

// Import Socket.IO and pass our HTTP server object to it.
const socketio = require("socket.io")(http, {
    wsEngine: 'ws'
});

let roomPassArr = [];
let socketArr = [];
// Attach our Socket.IO server to our HTTP server to listen
const io = socketio.listen(server);
io.sockets.on("connection", function (socket) {   // This callback runs when a new Socket.IO connection is established.
    socket.on('message_to_server', function (data) {
        // This callback runs when the server receives a new message from the client.
        console.log("message: " + data.message + "room num" + data.room  + "username: " + data.username);
        // log it to the Node.JS output
        io.sockets.to(data.room).emit("message_to_client",{msg: data.message, usr:data.username, room: data.room}); // broadcast the message to other users
	console.log(socketArr);
});

    socket.on('enter_room', function (data) {
	socket.join(data.room);
	socketArr.push({username: data.username, id: socket.id});
	console.log(socketArr);
	console.log("username: " + data.username + "room num:" + data.room);
	io.sockets.to(data.room).emit("tester", {usr: data.username, room: data.room});
	console.log("username: " + data.username + "room num:" + data.room);
});
    socket.on('disconnecter', function (data){
	socket.leave(data.room);
	console.log(data.username + " has left the room");
	io.sockets.to(data.room).emit("leave_room", {usr: data.username, room:data.room});

});
    socket.on("create_pass_room", function(data) {
	socket.join(data.room);
	let roomy = data.room;
	let passy = data.password;
	roomPassArr.push({roomName:roomy, password:passy});
	console.log(roomPassArr);
	console.log("username: " + data.username + "room num:" + data.room + "password" + data.password);
	io.sockets.to(data.room).emit("create_p_room", {user: data.username, room: data.room, pass: data.password});

});
    socket.on("join_pass_room", function(data) {
	let rguess = data.roomguess;
	let pguess = data.passguess;
	console.log(data);
	let bool = false;
	for(let i = 0; i< roomPassArr.length; i++){
		if(roomPassArr[i].roomName == rguess && roomPassArr[i].password == pguess){
			socket.join(data.roomguess);
			bool = true;
			console.log("username: " + data.username + "room num:" + data.roomguess);
			io.sockets.to(data.roomguess).emit("join_p_room", {user:data.username, room:data.roomguess, pass:data.passguess});
}
	}
	if (bool == false){
		io.sockets.emit("badguess", data);
}
});
    socket.on('kicker', function(data) {
	let connectedClients = Object.keys(io.of('/namespace').clients().connected);
	for(let i = 0; i<connectedClients.length; i++){
		if(data.username == connectedClients[i]){
			socket = connectedClients[i];
	}
	}
	socket.leave(data.room);
	console.log(data.username + " has been kicked from the room " );
	io.sockets.to(data.room).emit("kicked", {usr:data.username, room:data.room});
});
    socket.on('private_message', function (data){
	let from = data.userFrom;
	let rec = data.userTo;
	let msg = data.message;
	for(let i = 0; i<socketArr.length; i++){
		if(rec ==  socketArr[i].username){
			io.sockets.to(socket.id).to(socketArr[i].id).emit("pm", {from:from, to:rec, message:msg});
			}
}
	io.sockets.to(socket.id).to(data.userTo).emit("pm", {from:from, to:rec, message:msg});
	console.log(" message from " + from + " to " + rec  + msg);
});
});
