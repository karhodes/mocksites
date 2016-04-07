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
}	