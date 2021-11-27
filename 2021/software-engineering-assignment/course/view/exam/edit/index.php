<?php
require_once(__DIR__ . "/../../../../includes/constants.php");
include(__DIR__ . "/../../../../includes/session.php");

if ($user_role !== 'tutor') {
    header('location: ' . ROOT_SITE . '/access/');
}

$saved = false;
if ((isset($_GET['exam']) && isset($_GET['question'])) || (isset($_POST['exam']) && isset($_POST['question']))) {
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
        $saved = true;
        $question_text = $_POST['question-name'];
        $correct_answer = $_POST['correct-answer'];
        $question_id = $question['question_id'];
        $query = "UPDATE exam_question SET question_name = '$question_text' WHERE question_id = $question_id";
        mysqli_query($db, $query) or die(mysqli_error($db));
        $query = "SELECT choice_id FROM exam_choice WHERE question_id = $question_id";
        $choice_result = mysqli_query($db, $query) or die(mysqli_error($db));
        for ($i = 0, $len = mysqli_num_rows($choice_result); $i < $len; $i++) {
            $row = mysqli_fetch_array($choice_result);
            $choice_id = $row['choice_id'];
            $choice_text = $_POST['question-text-' . $i];
            $query = "UPDATE exam_choice SET choice_text = '$choice_text', choice_correct = 0 WHERE choice_id = '$choice_id'";
            mysqli_query($db, $query) or die(mysqli_error($db));
            if ($choice_id = $correct_answer) {
                $query = "UPDATE exam_choice SET choice_correct = 1 WHERE choice_id = '$choice_id'";
                mysqli_query($db, $query) or die(mysqli_error($db));
            }
        }

        $query = "SELECT question_id, question_name FROM exam_question WHERE schedule_id = '$schedule[0]' AND question_id = '$question_id'";
        $result = mysqli_query($db, $query) or die(mysqli_error($db));
        $question = mysqli_fetch_array($result);
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
                    Editing Question
                </div>
                <div class="content-element content-wrapper">
                    <form action="" method="post">
                        <input type="hidden" name="exam" value="<?php echo htmlspecialchars($_GET['exam']); ?>">
                        <input type="hidden" name="question" value="<?php echo htmlspecialchars($_GET['question']); ?>">
                        <label for="question-name">Question Name</label>
                        <textarea style="width:100%;" name="question-name" id="question-name"><?php echo $question['question_name'] ?></textarea>
                        <?php
                        $question_id = $question['question_id'];
                        $query = "SELECT choice_id, choice_text, choice_correct FROM exam_choice WHERE question_id = $question_id";
                        $choice_result = mysqli_query($db, $query) or die(mysqli_error($db));
                        $choices = [];
                        while ($row = mysqli_fetch_array($choice_result)) {
                            $choices[] = array($row['choice_id'], $row['choice_text'], $row['choice_correct']);
                        }
                        ?>
                        <div style="display:flex;flex-wrap:wrap;">
                            <?php for ($i = 0; $i < count($choices); $i++) : ?>
                                <div style="width:50%;">
                                    <span>Choice <?php echo $i + 1 ?></span>
                                    <input type="radio" id="correct-<?php echo $i ?>" name="correct-answer" value=<?php echo $choices[$i][0];
                                                                                                                    if ($choices[$i][2]) echo " checked" ?>>
                                    <label for="correct-<?php echo $i ?>">Correct?</label>
                                    <textarea style="width:100%;" name="question-text-<?php echo $i ?>"><?php echo $choices[$i][1] ?></textarea>
                                </div>
                            <?php endfor ?>
                        </div>
                        <br>
                        <div style="text-align:center;">
                            <input class="link-button" type="submit" value="Save" />
                            <a class="link-button" href="../?exam=<?php echo $schedule_id ?>">Back</a>
                        </div>
                    </form>
                    <?php if ($saved) : ?>
                        <div>Question saved...</div>
                    <?php endif ?>
                </div>
            </div>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>