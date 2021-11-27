<?php
require_once(__DIR__ . "/../../includes/constants.php");
include(__DIR__ . "/../../includes/session.php");

$query = "SELECT subject_id, subject_name FROM subject";
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
                    Publish Grading
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
                                $query = "SELECT schedule_id, schedule_name,schedule_start,schedule_end FROM schedule WHERE subject_id = '$subject[0]'";
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
                    <strong>No subjects in the list.</strong>
                <?php endif ?>
            </div>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>