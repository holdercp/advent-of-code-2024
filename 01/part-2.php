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

// Create a id => count map
$id_count = array_count_values($r_ids);

// Calculate the similarity score
$score = array_reduce($l_ids, function ($carry, $l) use ($id_count) {
    return $carry + $l * ($id_count[$l] ?? 0);
}, 0);

// Print the score
print_r($score);