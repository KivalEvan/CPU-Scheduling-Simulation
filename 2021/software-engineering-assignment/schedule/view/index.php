<?php
require_once(__DIR__ . "/../../includes/constants.php");
include(__DIR__ . "/../../includes/session.php");

$query = "SELECT subject_id FROM enrollment WHERE user_id = '$user_id'";
if ($user_role === 'eru') {
    $query = "SELECT subject_id FROM subject";
}
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
                    View Schedule
                </div>
                <br>
                <table>
                    <thead>
                        <tr>
                            <th class="table-join">Subject</th>
                            <th class="table-join">Exam Name</th>
                            <th class="table-join">Start Date & Time</th>
                            <th class="table-join">End Date & Time</th>
                        </tr>
                    </thead>
                    <?php if (count($subjects)) : ?>
                        <?php foreach ($subjects as $subject) : ?>
                            <?php
                            $query = "SELECT schedule_id, schedule_name, schedule_start, schedule_end FROM schedule WHERE subject_id = '$subject[0]'";
                            $result = mysqli_query($db, $query) or die(mysqli_error($db));
                            $schedules = [];
                            while ($row = mysqli_fetch_array($result)) {
                                $schedules[] = array($row['schedule_name'], $row['schedule_start'], $row['schedule_end'], $row['schedule_id']);
                            }
                            $first = true;
                            ?>
                            <?php if (count($schedules)) : ?>
                                <?php foreach ($schedules as $schedule) : ?>
                                    <tr class="table-join">
                                        <?php if ($first) : ?>
                                            <td rowspan=<?php if ($user_role === 'tutor') echo count($schedules) + 1;
                                                        elseif ($user_role === 'eru') {
                                                            echo count($schedules) * 2 + 1;
                                                        } else {
                                                            echo count($schedules);
                                                        };
                                                        $first = !$first; ?> class="table-join"><?php echo $subject[0] . ' - ' . $subject[1] ?></td>
                                        <?php endif ?>
                                        <td class="table-join"><?php echo $schedule[0] ?></td>
                                        <td class="table-join"><?php if (strtotime($schedule[1]) < strtotime(date('Y-m-d H:i:s'))) echo '<b>';
                                                                echo $schedule[1];
                                                                if (strtotime($schedule[1]) < strtotime(date('Y-m-d H:i:s'))) echo '</b>'; ?></td>
                                        <td class="table-join"><?php if (strtotime($schedule[1]) < strtotime(date('Y-m-d H:i:s'))) echo '<b>';
                                                                echo $schedule[2];
                                                                if (strtotime($schedule[1]) < strtotime(date('Y-m-d H:i:s'))) echo '</b>'; ?></td>
                                    </tr>
                                    <?php if ($user_role === 'eru') : ?>
                                        <tr class="table-join" style="text-align:center;">
                                            <td class="table-join"><a class="link-button" href="../edit/?subject=<?php echo $subject[0] ?>&schedule=<?php echo $schedule[3] ?>">Edit</a></td>
                                            <td class="table-join"><a class="link-button" href="../remove/?schedule=<?php echo $schedule[3] ?>">Remove</a></td>
                                            <td class="table-join"></td>
                                        </tr>
                                    <?php endif ?>
                                <?php endforeach ?>
                            <?php else : ?>
                                <tr class="table-join">
                                    <td <?php if ($user_role === 'tutor' || $user_role === 'eru') echo 'rowspan=2' ?> class="table-join"><?php echo $subject[0] . ' - ' . $subject[1] ?></td>
                                    <td colspan=3 class="table-join">No scheduled examination.</td>
                                </tr>
                            <?php endif ?>
                            <?php if ($user_role === 'tutor') : ?>
                                <tr class="table-join" style="text-align:center;">
                                    <td colspan=3 class="table-join"><a class="link-button" href="../book/?subject=<?php echo $subject[0] ?>">Book Schedule</a></td>
                                </tr>
                            <?php endif ?>
                            <?php if ($user_role === 'eru') : ?>
                                <tr class="table-join" style="text-align:center;">
                                    <td colspan=3 class="table-join"><a class="link-button" href="../book/?subject=<?php echo $subject[0] ?>">Add</a></td>
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