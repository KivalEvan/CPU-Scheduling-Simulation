<?php
require_once(__DIR__ . "/../../includes/constants.php");
include(__DIR__ . "/../../includes/session.php");

$query = "SELECT * FROM user WHERE user_id = '$user_id'";
$result = mysqli_query($db, $query) or die(mysqli_error($db));
$row = mysqli_fetch_array($result, MYSQLI_ASSOC);
$user_name = $row['user_name'];
$user_fname = $row['user_fname'];
$user_lname = $row['user_lname'];

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
                    Grading Report
                </div>
                <div class="content-element content-wrapper">
                    <table class="table-separate">
                        <tr>
                            <th>Name</th>
                            <td><?php echo $user_fname . ' ' . $user_lname ?></td>
                        </tr>
                        <tr>
                            <th>ID</th>
                            <td><?php echo $user_name ?></td>
                        </tr>
                    </table>
                    <br>
                    <hr>
                    <br>
                    <label for="semester"><b>Semester</b></label>
                    <select id="semester">
                        <option value="1">Trimester 1</option>
                        <option value="2">Trimester 2</option>
                        <option value="3">Trimester 3</option>
                    </select>
                    <label for="year"><b>Year</b></label>
                    <select id="year">
                        <option value="2019">2019</option>
                        <option value="2020">2020</option>
                        <option value="2021">2021</option>
                    </select>
                </div>
                <table>
                    <thead>
                        <tr>
                            <th>Subject</th>
                            <th>Exam Name</th>
                            <th>Grade</th>
                            <th>Marks</th>
                        </tr>
                    </thead>
                    <?php if (count($subjects)) : ?>
                        <?php foreach ($subjects as $subject) : ?>
                            <?php
                            $query = "SELECT schedule_id, schedule_name FROM schedule WHERE subject_id = '$subject[0]'";
                            $result = mysqli_query($db, $query) or die(mysqli_error($db));
                            $schedules = [];
                            while ($row = mysqli_fetch_array($result)) {
                                $schedules[] = array($row['schedule_id'], $row['schedule_name']);
                            }
                            $first = true;
                            ?>
                            <?php if (count($schedules)) : ?>
                                <?php foreach ($schedules as $schedule) : ?>
                                    <tr class="table-join">
                                        <?php if ($first) : ?>
                                            <td rowspan=<?php echo count($schedules);
                                                        $first = !$first; ?> class="table-join"><?php echo $subject[0] . ' - ' . $subject[1] ?></td>
                                        <?php endif ?>
                                        <?php
                                        $query = "SELECT grade_grading, grade_mark, grade_taken, grade_final FROM grade WHERE schedule_id = '$schedule[0]' AND user_id = '$user_id'";
                                        $result = mysqli_query($db, $query) or die(mysqli_error($db));
                                        $grade = mysqli_fetch_array($result, MYSQLI_ASSOC);
                                        ?>
                                        <td class="table-join"><?php echo $schedule[1] ?></td>
                                        <?php if ($grade) : ?>
                                            <td class="table-join"><?php echo $grade['grade_grading'] ?></td>
                                            <td class="table-join"><?php echo $grade['grade_mark'] ?></td>
                                        <?php else : ?>
                                            <td colspan=2 class="table-join">Not Taken.</td>
                                        <?php endif ?>
                                    </tr>
                                <?php endforeach ?>
                            <?php else : ?>
                                <tr class="table-join">
                                    <td class="table-join"><?php echo $subject[0] . ' - ' . $subject[1] ?></td>
                                    <td colspan=3 class="table-join">No examination taken.</td>
                                </tr>
                            <?php endif ?>
                        <?php endforeach ?>
                    <?php else : ?>
                        <tr class="table-join">
                            <td colspan=4>You are not enrolled</td>
                        </tr>
                    <?php endif ?>
                </table>
            </div>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>