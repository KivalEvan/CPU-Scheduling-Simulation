<?php
require_once(__DIR__ . "/../../includes/constants.php");
include(__DIR__ . "/../../includes/session.php");

$query = "SELECT subject_id FROM enrollment WHERE user_id = '$user_id'";
$result = mysqli_query($db, $query) or die(mysqli_error($db));
$subject_rows = [];
while ($row = mysqli_fetch_array($result)) {
    $subject_rows[] = $row['subject_id'];
}

$query = "SELECT subject_id, subject_name FROM subject WHERE subject_id IN(\"" . join('", "', $subject_rows) . "\")";
$result = mysqli_query($db, $query) or die(mysqli_error($db));
$subjects = [];
while ($row = mysqli_fetch_array($result)) {
    $subjects[] = array($row['subject_id'], $row['subject_name']);
}

?>

<!DOCTYPE html>
<html>

<head>
    <title>Online Objective Exam</title>
    <link rel="stylesheet" href="<?php echo ROOT_SITE ?>/assets/style.css">
</head>

<body>
    <?php include_once(ROOT_PATH . '/includes/header.php') ?>
    <main class="wrapper">
        <?php include_once(ROOT_PATH . '/includes/navigation.php') ?>
        <div class="content">
            <div class="content-wrapper">
                <div class="content-header">
                    Course Overview
                </div>
                <?php if (count($subjects)) : ?>
                    <?php foreach ($subjects as $subject) : ?>
                        <br>
                        <div>
                            <div class="content-header">
                                <?php echo $subject[0] . ' - ' . $subject[1] ?>
                            </div>
                            <div class="content-element content-wrapper">
                                <?php
                                $query = "SELECT schedule_id, schedule_name, schedule_start, schedule_end FROM schedule WHERE subject_id = '$subject[0]'";
                                $result = mysqli_query($db, $query) or die(mysqli_error($db));
                                $schedules = [];
                                while ($row = mysqli_fetch_array($result)) {
                                    $schedules[] = array($row['schedule_id'], $row['schedule_name'], $row['schedule_start'], $row['schedule_end']);
                                }
                                ?>
                                <?php if (count($schedules) > 0) : ?>
                                    <?php foreach ($schedules as $schedule) : ?>
                                        <div style="display:flex;">
                                            <div style="flex:1;vertical-align:middle;"><span style="display:block;padding:0.5em 0;"><?php echo $schedule[1] ?></span></div>
                                            <?php if ($user_role === 'tutor') : ?>
                                                <?php if (strtotime(date('Y-m-d H:i:s')) < strtotime($schedule[2])) : ?>
                                                    <span title="<?php echo $schedule[2] ?>" class="link-button">Scheduled</span>
                                                <?php else : ?>
                                                    <?php
                                                    if (strtotime(date('Y-m-d H:i:s')) < strtotime($schedule[3])) :
                                                    ?>
                                                        <span title="<?php echo $schedule[2] ?>" class="link-button">On-going</span>
                                                    <?php else : ?>
                                                        <a class="link-button" href="./finalise/?exam=<?php echo $schedule[0] ?>">Finalise</a>
                                                    <?php endif ?>
                                                <?php endif ?>
                                                <a class="link-button" href="./exam/?exam=<?php echo $schedule[0] ?>">View</a>
                                            <?php endif ?>
                                            <?php if ($user_role === 'student') : ?>
                                                <?php if (strtotime(date('Y-m-d H:i:s')) < strtotime($schedule[2])) : ?>
                                                    <span title="<?php echo $schedule[2] ?>" class="link-button">Scheduled</span>
                                                <?php else : ?>
                                                    <?php
                                                    $query = "SELECT user_id FROM exam_answer, exam_question WHERE exam_answer.user_id = '$user_id' AND exam_answer.question_id = exam_question.question_id";
                                                    $result = mysqli_query($db, $query) or die(mysqli_error($db));
                                                    if (mysqli_num_rows($result)) :
                                                    ?>
                                                        <span title="<?php echo $schedule[2] ?>" class="link-button">Taken</span>
                                                    <?php else : ?>
                                                        <a class="link-button" href="./exam/?exam=<?php echo $schedule[0] ?>">Take Exam</a>
                                                    <?php endif ?>
                                                <?php endif ?>
                                            <?php endif ?>
                                        </div>
                                        <br>
                                    <?php endforeach ?>
                                <?php else : ?>
                                    No scheduled examination.
                                <?php endif ?>
                            </div>
                        </div>
                    <?php endforeach ?>
                <?php else : ?>
                    <strong>You are not enrolled.</strong>
                <?php endif ?>
            </div>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>