<?php
require_once(__DIR__ . "/../../../includes/constants.php");
include(__DIR__ . "/../../../includes/session.php");

if (isset($_GET['exam'])) {
    $schedule_id = $_GET['exam'];
    $query = "SELECT schedule_id, subject_id, schedule_name FROM schedule WHERE schedule_id = '$schedule_id'";
    $result = mysqli_query($db, $query) or die(mysqli_error($db));
    $schedule = mysqli_fetch_array($result);
    if (!$schedule) {
        header('location: ' . ROOT_SITE . '/access/');
    }

    $query = "SELECT question_id, question_name FROM exam_question WHERE schedule_id = '$schedule[0]'";
    $question_result = mysqli_query($db, $query) or die(mysqli_error($db));
    $questions = [];
    while ($row = mysqli_fetch_array($question_result)) {
        $questions[] = array($row['question_id'], $row['question_name']);
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
                    Exam Content
                </div>
                <br>
                <div class="content-header"><?php echo $schedule[1] . ' - ' . $schedule[2] ?></div>
                <div class="content-element content-wrapper">
                    <form action="" method="post">
                        <input type="hidden" name="exam" value="<?php echo htmlspecialchars($_GET['exam']); ?>">
                        <?php if (count($questions) > 0) : ?>
                            <?php for ($i = 0; $i < count($questions); $i++) : ?>
                                <div>
                                    <strong>Question <?php echo $i + 1 ?></strong>
                                    <p><b><?php echo $questions[$i][1] ?></b></p>
                                    <?php
                                    $question_id = $questions[$i][0];
                                    $query = "SELECT choice_id, choice_text FROM exam_choice WHERE question_id = $question_id";
                                    $choice_result = mysqli_query($db, $query) or die(mysqli_error($db));
                                    $choices = [];
                                    while ($row = mysqli_fetch_array($choice_result)) {
                                        $choices[] = array($row['choice_id'], $row['choice_text']);
                                    }
                                    ?>
                                    <div style="display:flex;flex-wrap:wrap;">
                                        <?php foreach ($choices as $choice) : ?>
                                            <div style="width:50%;">
                                                <input type="radio" id=<?php echo $choice[0] ?> name=<?php echo $questions[$i][0] ?> value=<?php echo $choice[0] ?>>
                                                <label for=<?php echo $choice[0] ?>><?php echo $choice[1] ?></label>
                                            </div>
                                        <?php endforeach ?>
                                    </div>
                                    <?php if ($user_role === 'tutor') : ?>
                                        <div style="text-align:center;margin:0.25em 0;">
                                            <a class="link-button" href="./edit/?exam=<?php echo $schedule_id ?>&question=<?php echo $questions[$i][0] ?>">Edit</a>
                                            <a class="link-button" href="./remove/?exam=<?php echo $schedule_id ?>&question=<?php echo $questions[$i][0] ?>">Remove</a>
                                        </div>
                                    <?php endif ?>
                                </div>
                                <hr>
                            <?php endfor ?>
                        <?php else : ?>
                            No question available.
                        <?php endif ?>
                        <br>
                        <?php if ($user_role === 'tutor') : ?>
                            <div style="text-align:center;">
                                <a class="link-button" href="./add/?exam=<?php echo $schedule_id ?>">Add New Question</a>
                            </div>
                        <?php endif ?>
                        <?php if ($user_role === 'student') : ?>
                            <div style="text-align:center;">
                                <input class="link-button" type="submit" value="Submit Answer">
                            </div>
                        <?php endif ?>
                    </form>
                </div>
            </div>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>