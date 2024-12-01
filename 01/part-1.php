<?php
$input = file_get_contents(__DIR__ . "/input.txt");
$input = explode("\n", $input);

// Separate the input into left and right ids
$l_ids = [];
$r_ids = [];
foreach ($input as $line) {
	[$l, $r] = explode("   ", $line);
	$l_ids[]= (int) $l;
	$r_ids[]= (int) $r;
}

// Sort the ids
sort($l_ids);
sort($r_ids);

// Left id is key, right id is value
$combined = array_combine($l_ids, $r_ids);
$distance = 0;
foreach ($combined as $l => $r) {
	$distance += abs($r - $l);
}

print_r($distance);
