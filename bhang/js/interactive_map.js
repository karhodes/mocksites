$(document).ready(function() {

	// --- dot code
	// --- when the dot is clicked
	$('a.dot').click(function(){
		// --- remove selected class from all dots (change to red)
		$('a.dot').removeClass("selected");

		// --- add selected class on clicked anchor (change to green)
		$(this).addClass("selected");

		// --- create a variable to hold info for matching div
		var spot = ".spot_detail#" + $(this).attr("spot");

		// --- variable to hold html code
		var htmlCode = $(spot).html();

		// --- animate the container; fade in & out
		$(".detail_container").fadeOut(500, function(){
			// --- the container is hidden
			// --- put the html in the container and fade back in
			$(".detail_container .spot_detail").html(htmlCode);
			$(".detail_container").fadeIn(500); 
		}) // closes detail container

	}) // closes dot code

}); // closes document.ready