window.onload = function() {
	console.log("images loaded");

	var theCanvas = document.getElementById('bhang_logo_canvas');
	if (theCanvas && theCanvas.getContext) {
		var ctx = theCanvas.getContext("2d");
		if (ctx) {

     		// create a variable to hold the image
     		var srcImg = document.getElementById("bhang_logo_cream");

     		// draw an image directly onto the canvas at the top left
     		ctx.drawImage(srcImg,0,0,200,100);
		}
	}
}