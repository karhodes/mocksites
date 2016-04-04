<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Kitty Kibble Dispenser</title>
    
    <!-- Fonts, Bootstrap & CSS -->
    <link href='https://fonts.googleapis.com/css?family=Lobster' rel='stylesheet' type='text/css'>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css"> 
    <link rel="stylesheet" href="css/styles.css">

</head>
<body>

<div class="row">
    <div class="col-md-6 col-md-offset-3">

    <h1>Kitty Kibble Dispenser</h1>

<?php

    

    date_default_timezone_set('America/New_York');

    $json = file_get_contents('http://data.sparkfun.com/output/0lxrKzMxG7IrmbKa1Q0Q.json');
    $obj = json_decode($json, true);
    // echo $obj->access_token;

    // $ch = curl_init("http://www.phponwebsites.com/json.php"); // add your url which contains json file
    // curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    // $content = curl_exec($ch);
    // curl_close($ch);
    // $json = json_decode($content, true);
    
    // print_R($obj);
    $count=count($obj);

    
    echo'<table class="table"><tr><th>Cat</th><th>Cat ID</th><th>Cat Name</th><th>Time Fed</th><tr>';
    for($i=0;$i<$count-55;$i++)
    {
      
        $a = new \DateTime($obj[$i]['timestamp']);
        $date = $a->format('g:ia \o\n l jS F Y');
        // var_dump($b);


      echo'<tr><td><img src="images/' . $obj[$i]['cat'] . '.png"/></td>
      <td>'.$obj[$i]['catid'].'</td>
      <td>'.$obj[$i]['cat'].'</td>
      <td>'.$date.'</td></tr>';
    }
    echo'</table>';
    

?>

    </div>
</div>
</body>