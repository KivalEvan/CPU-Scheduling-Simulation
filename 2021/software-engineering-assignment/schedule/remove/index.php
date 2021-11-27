<?php
require_once(__DIR__ . "/../../../../includes/constants.php");
include(__DIR__ . "/../../../../includes/session.php");

if ($user_role !== 'tutor') {
    header('location: ' . ROOT_SITE . '/access/');
}

if (isset($_GET['exam']) && isset($_GET['question'])) {
    $schedule_id = $_GET['exam'];
    $query = "SELECT schedule_id, subject_id, schedule_name FROM schedule WHERE schedule_id = '$schedule_id'";
    $result = mysqli_query($db, $query) or die(mysqli_error($db));
    $schedule = mysqli_fetch_array($result);
    if (!$schedule) {
        header('location: ' . ROOT_SITE . '/access/');
    }

    $question_id = $_GET['question'];
    $query = "SELECT question_id, question_name FROM exam_question WHERE schedule_id = '$schedule[0]' AND question_id = '$question_id'";
    $result = mysqli_query($db, $query) or die(mysqli_error($db));
    $question = mysqli_fetch_array($result);
    if (!$question) {
        header('location: ' . ROOT_SITE . '/access/');
    }
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $query = "DELETE FROM exam_choice WHERE question_id = '$question_id'";
        mysqli_query($db, $query) or die(mysqli_error($db));

        $query = "DELETE FROM exam_question WHERE question_id = '$question_id'";
        mysqli_query($db, $query) or die(mysqli_error($db));

        header('location: ../?exam=' . $schedule_id);
    }
} else {
    header('location: ' . ROOT_SITE . '/access/');
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
                    Are you sure you want to remove this question?
                </div>
                <div class="content-element content-wrapper">
                    <p><b><?php echo $question['question_name'] ?></b></p>
                    <?php
                    $question_id = $question['question_id'];
                    $query = "SELECT choice_id, choice_text FROM exam_choice WHERE question_id = $question_id";
                    $choice_result = mysqli_query($db, $query) or die(mysqli_error($db));
                    $choices = [];
                    while ($row = mysqli_fetch_array($choice_result)) {
                        $choices[] = $row['choice_text'];
                    }
                    ?>
                    <div style="display:flex;flex-wrap:wrap;">
                        <?php foreach ($choices as $choice) : ?>
                            <div style="width:50%;">
                                <span><?php echo $choice ?></span>
                            </div>
                        <?php endforeach ?>
                    </div>
                    <br>
                    <form action="" method="post" style="text-align:center;">
                        <input class="link-button" type="submit" value="Yes" />
                        <a class="link-button" href="../?exam=<?php echo $schedule_id ?>">No</a>
                    </form>
                </div>
            </div>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>