<?php
require_once(__DIR__ . "/../../../../includes/constants.php");
include(__DIR__ . "/../../../../includes/session.php");

if ($user_role !== 'tutor') {
    header('location: ' . ROOT_SITE . '/access/');
}

if (isset($_GET['exam'])) {
    $schedule_id = $_GET['exam'];
    $query = "SELECT schedule_id FROM schedule WHERE schedule_id = '$schedule_id'";
    $result = mysqli_query($db, $query) or die(mysqli_error($db));
    $schedule = mysqli_fetch_array($result);
    if (!$schedule) {
        header('location: ' . ROOT_SITE . '/access/');
    }

    // add question
    $query = "INSERT INTO exam_question(schedule_id, question_name) VALUES ($schedule_id, 'New question')";
    mysqli_query($db, $query) or die(mysqli_error($db));

    // get question_id
    $query = "SELECT question_id FROM exam_question WHERE schedule_id = '$schedule_id'";
    $result = mysqli_query($db, $query) or die(mysqli_error($db));
    while ($row = mysqli_fetch_array($result)) {
        $question_id = $row['question_id'];
    }

    // fill choice
    for ($i = 1; $i <= 4; $i++) {
        $query = "INSERT INTO exam_choice(question_id, choice_text) VALUES ($question_id, 'Choice $i')";
        mysqli_query($db, $query);
    }

    header('location: ../?exam=' . $schedule_id);
} else {
    header('location: ' . ROOT_SITE . '/access/');
}
