window.onload = function() {
	console.log("team js loaded");


	// action shots will show when the user hovers over the profile pic
	$('.pic_inner_container').hover(function(){
		$(this).children(".profile_photo").toggle( "blind" );
  	})

  	/* ============= Open & Close Skater Bio =================== */

	// --- pic_inner_container code
	// --- when the pic_inner_container is clicked
	$('.pic_inner_container').click(function(){
		// --- remove selected class from all skaters (revert to light-olive border)
		$('.pic_inner_container').removeClass("selected_skater");

		// --- add selected class on clicked anchor (change to mint border)
		$(this).addClass("selected_skater");

		// --- create a variable to hold info for matching div
		var skater = ".skater_detail#" + $(this).attr("skater");

		// --- variable to hold html code
		var htmlCode = $(skater).html();

		// --- animate the container; fade in & out
		$(".skater_detail_inner_container").fadeOut(500, function(){
			// --- the container is hidden
			// --- put the html in the container and fade back in
			$(".skater_detail_inner_container .skater_detail").html(htmlCode);
			$(".skater_detail_inner_container").fadeIn(500); 
		}) // closes detail container

	}) // closes skater bio code

	/* ============= Team Canvas =================== */

	var theCanvas = document.getElementById('team_canvas');
	if (theCanvas && theCanvas.getContext) {
		var ctx = theCanvas.getContext("2d");
		if (ctx) {

			var width = theCanvas.width;
			console.log(width);
			var r = 10;
			var CX = 10;
			numTimes = width / (2*r);

			for(var i=0; i<numTimes; i++){
				ctx.beginPath();
				ctx.arc(CX,10,r,0,2*Math.PI);
				ctx.fillStyle = '#36362C';
				ctx.fill();

				CX = CX + 2*r;

			}

		}
	}



}	