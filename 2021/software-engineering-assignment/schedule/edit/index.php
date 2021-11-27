<?php
require_once(__DIR__ . "/../../includes/constants.php");
include(__DIR__ . "/../../includes/session.php");

if ($user_role !== 'eru') {
    header('location: ' . ROOT_SITE . '/access/');
}

if (isset($_GET['subject']) || isset($_POST['subject'])) {
    $subject_id = $_GET['subject'];

    $query = "SELECT subject_name FROM subject WHERE subject_id = '$subject_id'";
    $result = mysqli_query($db, $query) or die(mysqli_error($db));
    $row = mysqli_fetch_array($result, MYSQLI_ASSOC);
    $subject_name = $row['subject_name'];

    $query = "SELECT schedule_id, schedule_name FROM schedule WHERE subject_id = '$subject_id'";
    $schedule_result = mysqli_query($db, $query) or die(mysqli_error($db));
    $schedules = [];
    while ($row = mysqli_fetch_array($schedule_result)) {
        $schedules[] = array($row['schedule_id'], $row['schedule_name']);
    }

    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $schedule_name = $_POST['booking-name'];
        $start_date = $_POST['start-date'];
        $start_time = $_POST['start-time'];
        $schedule_start = date('Y-m-d H:i:s', strtotime($start_date . ' ' . $start_time));
        $end_date = $_POST['end-date'];
        $end_time = $_POST['end-time'];
        $schedule_end = date('Y-m-d H:i:s', strtotime($end_date . ' ' . $end_time));

        $query = "INSERT INTO schedule(subject_id, schedule_name, schedule_start, schedule_end) VALUES ('$subject_id', '$schedule_name', '$schedule_start', '$schedule_end')";
        mysqli_query($db, $query) or die(mysqli_error($db));
        header('location: ../view/');
    }
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
                    Edit Schedule
                </div>
                <br>
                <?php if (isset($_GET['subject'])) : ?>
                    <div class="content-header">
                        <?php echo $subject_id . ' - ' . $subject_name ?>
                    </div>
                    <div class="content-element content-wrapper">
                        <form style="display:flex;flex-wrap:wrap;" action="" method="post">
                            <div style="width:100%;">
                                <input type="hidden" name="subject" value="<?php echo htmlspecialchars($_GET['subject']) ?>">
                                <label for="booking-name">Booking Name: </label>
                                <input type="text" name="booking-name" id="booking-name" value="Booking Name">
                            </div>
                            <div style="width:50%;">
                                <span>Start Time</span><br>
                                <input type="date" name="start-date">
                                <input type="time" name="start-time">
                            </div>
                            <div style="width:50%;">
                                <span>End Time</span><br>
                                <input type="date" name="end-date">
                                <input type="time" name="end-time">
                            </div>
                            <div style="width:100%;text-align:center;">
                                <br>
                                <input class="link-button" type="submit" value="Edit Booking">
                            </div>
                        </form>
                    </div>
                <?php else : ?>
                    <div class="content-header">
                        Select Subject to Edit Schedule
                    </div>
                    <div class="content-element content-wrapper">
                        <form style="text-align:center;">
                            <?php
                            $query = "SELECT subject_id, subject_name FROM subject";
                            $result = mysqli_query($db, $query) or die(mysqli_error($db));
                            $subjects = [];
                            while ($row = mysqli_fetch_array($result)) {
                                $subjects[] = array($row['subject_id'], $row['subject_name']);
                            }
                            ?>
                            <label for="subject">Subject list: </label>
                            <select id="subject" name="subject">
                                <?php foreach ($subjects as $subject) : ?>
                                    <option value=<?php echo $subject[0] ?>><?php echo $subject[0] . ' - ' . $subject[1] ?></option>
                                <?php endforeach ?>
                            </select>
                            <br>
                            <br>
                            <input class="link-button" type="submit" value="Confirm Subject">
                        </form>
                    </div>
                <?php endif ?>
            </div>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>