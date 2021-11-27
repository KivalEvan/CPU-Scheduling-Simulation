<?php
require_once(__DIR__ . "/../includes/constants.php");
include(__DIR__ . '/../includes/session.php');

if (!isset($_SESSION["user"])) {
    header("location: " . ROOT_SITE . "/login/");
}
// im just lazy to do this but like not like i care how this look
$query = "SELECT * FROM user WHERE user_id = '$user_id'";
$result = mysqli_query($db, $query) or die(mysqli_error($db));
$row = mysqli_fetch_array($result, MYSQLI_ASSOC);
$user_name = $row['user_name'];
$user_fname = $row['user_fname'];
$user_lname = $row['user_lname'];
$user_id = $row['user_id'];
$user_email = $row['user_email'];
$user_phone = $row['user_phone'];

$query = "SELECT course_id, subject_id FROM enrollment WHERE user_id = '$user_id'";
$result = mysqli_query($db, $query) or die(mysqli_error($db));
$course_rows = [];
$subject_rows = [];
while ($row = mysqli_fetch_array($result)) {
    $course_rows[] = $row['course_id'];
    $subject_rows[] = $row['subject_id'];
}

$query = "SELECT course_name, course_faculty FROM course WHERE course_id IN(\"" . join('", "', $course_rows) . "\")";
$result = mysqli_query($db, $query) or die(mysqli_error($db));
$course_name_rows = [];
$course_faculties_rows = [];
while ($row = mysqli_fetch_array($result)) {
    $course_name_rows[] = $row['course_name'];
    $course_faculties_rows[] = $row['course_faculty'];
}

$query = "SELECT subject_id, subject_name FROM subject WHERE subject_id IN(\"" . join('", "', $subject_rows) . "\")";
$result = mysqli_query($db, $query) or die(mysqli_error($db));
$subject_rows = [];
while ($row = mysqli_fetch_array($result)) {
    $subject_rows[] = array($row['subject_id'], $row['subject_name']);
}

?>

<!DOCTYPE html>
<html>

<head>
    <title>Online Objective Exam</title>
    <link rel="stylesheet" href="../assets/style.css">
</head>

<body>
    <?php include_once(ROOT_PATH . '/includes/header.php') ?>
    <main class="wrapper">
        <?php include_once(ROOT_PATH . '/includes/navigation.php') ?>
        <div class="content">
            <div class="content-wrapper">
                <div class="content-header">
                    <?php echo ucfirst($user_role) ?> Profile
                </div>
                <div class="content-element content-wrapper">
                    <table class="table-separate">
                        <tr>
                            <th>Name</th>
                            <td colspan="4"><?php echo $user_fname . ' ' . $user_lname ?></td>
                        </tr>
                        <tr>
                            <th>ID</th>
                            <td><?php echo $user_name ?></td>
                            <th>Email</th>
                            <td colspan="2"><?php echo $user_email ?></td>
                        </tr>
                        <tr>
                            <th>Phone</th>
                            <td><?php echo $user_phone ?></td>
                            <th></th>
                            <th></th>
                            <th></th>
                        </tr>
                        <tr>
                            <th>Faculty</th>
                            <td colspan="4"><?php if (count($course_faculties_rows)) {
                                                echo join(', ', $course_faculties_rows);
                                            } else {
                                                echo "-";
                                            } ?></td>
                        </tr>
                        <tr>
                            <th>Course</th>
                            <td colspan="4"><?php if (count($course_name_rows)) {
                                                echo join(', ', $course_name_rows);
                                            } else {
                                                echo "-";
                                            } ?></td>
                        </tr>
                    </table>
                    <hr>
                    <div>
                        <table class="table-separate">
                            <tr>
                                <th>
                                    <label for="semester"><b>Semester</b></label>
                                </th>
                                <th>
                                    <select id="semester">
                                        <option value="1">Trimester 1</option>
                                        <option value="2">Trimester 2</option>
                                        <option value="3">Trimester 3</option>
                                    </select>
                                </th>
                                <th>
                                    <label for="year"><b>Year</b></label>
                                </th>
                                <th>
                                    <select id="year">
                                        <option value="2019">2019</option>
                                        <option value="2020">2020</option>
                                        <option value="2021">2021</option>
                                    </select>
                                </th>
                            </tr>
                            <?php if (count($subject_rows) > 0) : ?>
                                <?php foreach ($subject_rows as $subject) : ?>
                                    <tr>
                                        <td class="dark"><?php echo $subject[0] ?></td>
                                        <td colspan="3" class="dark"><?php echo $subject[1] ?></td>
                                    </tr>
                                <?php endforeach ?>
                            <?php else : ?>
                                <th>You are not enrolled.</th>
                            <?php endif ?>
                        </table>
                    </div>
                </div>
            </div>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>