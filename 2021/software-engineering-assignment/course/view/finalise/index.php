<?php
require_once(__DIR__ . "/../../../includes/constants.php");
include(__DIR__ . "/../../../includes/session.php");

if ($user_role !== 'tutor') {
    header('location: ' . ROOT_SITE . '/access/');
}

if (isset($_GET['exam']) || isset($_POST['exam'])) {
    $schedule_id = $_GET['exam'] || $_POST['exam'];
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
                            <table class="table-separate">
                                <tr>
                                    <th>Total number of questions</th>
                                    <td><?php echo count($questions) ?></td>
                                </tr>
                                <tr>
                                    <th>Marks allocated per question</th>
                                    <td><input type="number" name="marks" value="1"></td>
                                </tr>
                                <tr>
                                    <th>Implement Grading</th>
                                    <td>
                                        <table>
                                            <thead style="color:white;">
                                                <th colspan=3>Mark Range</th>
                                                <th>Grade</th>
                                                <tr></tr>
                                            </thead>
                                            <tr>
                                                <td><input type="number" name="marks" value="8"></td>
                                                <td>to</td>
                                                <td><input type="number" name="marks" value="10"></td>
                                                <td><input type="text" name="grading" value="A"></td>
                                            </tr>
                                            <tr>
                                                <td><input type="number" name="marks" value="5"></td>
                                                <td>to</td>
                                                <td><input type="number" name="marks" value="7"></td>
                                                <td><input type="text" name="grading" value="B"></td>
                                            </tr>
                                            <tr>
                                                <td><input type="number" name="marks" value="2"></td>
                                                <td>to</td>
                                                <td><input type="number" name="marks" value="4"></td>
                                                <td><input type="text" name="grading" value="C"></td>
                                            </tr>
                                            <tr>
                                                <td><input type="number" name="marks" value="0"></td>
                                                <td>to</td>
                                                <td><input type="number" name="marks" value="1"></td>
                                                <td><input type="text" name="grading" value="F"></td>
                                            </tr>
                                        </table>
                                    </td>
                                </tr>
                            </table>
                        <?php else : ?>
                            Exam had no questions.
                        <?php endif ?>
                        <br>
                        <?php if ($user_role === 'tutor') : ?>
                            <div style="text-align:center;">
                                <a class="link-button" href="./add/?exam=<?php echo $schedule_id ?>">Add New Question</a>
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