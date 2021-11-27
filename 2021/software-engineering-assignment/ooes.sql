-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Nov 21, 2021 at 08:07 AM
-- Server version: 10.4.21-MariaDB
-- PHP Version: 8.0.12
SET
  SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET
  time_zone = "+00:00";
  /*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
  /*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
  /*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
  /*!40101 SET NAMES utf8mb4 */;
--
  -- Database: `ooes`
  --
  -- --------------------------------------------------------
  --
  -- Table structure for table `course`
  --
  CREATE TABLE `course` (
    `course_id` varchar(7) NOT NULL,
    `course_name` varchar(63) NOT NULL,
    `course_faculty` varchar(63) NOT NULL
  ) ENGINE = InnoDB DEFAULT CHARSET = utf8mb4;
--
  -- Dumping data for table `course`
  --
INSERT INTO
  `course` (`course_id`, `course_name`, `course_faculty`)
VALUES
  (
    'BCS',
    'Bachelor of Computer Science',
    'Faculty of Communication and Information'
  ),
  (
    'BOE',
    'Bachelor of Engineering',
    'Faculty of Engineering'
  ),
  (
    'FIT',
    'Foundation in IT',
    'Faculty of Communication and Information'
  );
-- --------------------------------------------------------
  --
  -- Table structure for table `enrollment`
  --
  CREATE TABLE `enrollment` (
    `user_id` int(11) NOT NULL,
    `subject_id` varchar(7) NOT NULL,
    `course_id` varchar(7) NOT NULL,
    `enrol_start` timestamp NULL DEFAULT NULL,
    `enrol_end` timestamp NULL DEFAULT NULL
  ) ENGINE = InnoDB DEFAULT CHARSET = utf8mb4;
--
  -- Dumping data for table `enrollment`
  --
INSERT INTO
  `enrollment` (
    `user_id`,
    `subject_id`,
    `course_id`,
    `enrol_start`,
    `enrol_end`
  )
VALUES
  (
    3,
    'TCP2451',
    'BCS',
    '2021-11-18 08:00:37',
    '2021-11-30 08:00:37'
  ),
  (
    3,
    'TSE2101',
    'BCS',
    '2021-11-18 08:00:37',
    '2021-11-30 08:00:37'
  ),
  (
    4,
    'TCP2451',
    'BCS',
    '2021-11-18 07:54:13',
    '2021-11-30 07:54:13'
  ),
  (
    4,
    'TSE2101',
    'BCS',
    '2021-11-18 07:54:13',
    '2021-11-30 07:54:13'
  );
-- --------------------------------------------------------
  --
  -- Table structure for table `exam_answer`
  --
  CREATE TABLE `exam_answer` (
    `user_id` int(11) NOT NULL,
    `question_id` int(11) NOT NULL,
    `choice_id` int(11) NOT NULL
  ) ENGINE = InnoDB DEFAULT CHARSET = utf8mb4;
-- --------------------------------------------------------
  --
  -- Table structure for table `exam_choice`
  --
  CREATE TABLE `exam_choice` (
    `choice_id` int(11) NOT NULL,
    `question_id` int(11) NOT NULL,
    `choice_text` varchar(127) NOT NULL,
    `choice_correct` tinyint(1) NOT NULL
  ) ENGINE = InnoDB DEFAULT CHARSET = utf8mb4;
--
  -- Dumping data for table `exam_choice`
  --
INSERT INTO
  `exam_choice` (
    `choice_id`,
    `question_id`,
    `choice_text`,
    `choice_correct`
  )
VALUES
  (1, 1, 'Software is an instruction set', 1),
  (2, 1, 'Software is the opposite of hardware', 0),
  (3, 1, 'Software is a computer language', 0),
  (4, 1, 'None of the above', 0);
-- --------------------------------------------------------
  --
  -- Table structure for table `exam_question`
  --
  CREATE TABLE `exam_question` (
    `question_id` int(11) NOT NULL,
    `schedule_id` int(11) NOT NULL,
    `question_name` varchar(127) NOT NULL
  ) ENGINE = InnoDB DEFAULT CHARSET = utf8mb4;
--
  -- Dumping data for table `exam_question`
  --
INSERT INTO
  `exam_question` (`question_id`, `schedule_id`, `question_name`)
VALUES
  (1, 1, 'What is a software?');
-- --------------------------------------------------------
  --
  -- Table structure for table `grade`
  --
  CREATE TABLE `grade` (
    `user_id` int(11) NOT NULL,
    `schedule_id` int(11) NOT NULL,
    `grade_mark` float DEFAULT 0,
    `grade_grading` varchar(3) DEFAULT 'O',
    `grade_taken` tinyint(1) NOT NULL DEFAULT 0,
    `grade_final` tinyint(1) NOT NULL DEFAULT 0
  ) ENGINE = InnoDB DEFAULT CHARSET = utf8mb4;
--
  -- Dumping data for table `grade`
  --
INSERT INTO
  `grade` (
    `user_id`,
    `schedule_id`,
    `grade_mark`,
    `grade_grading`,
    `grade_taken`,
    `grade_final`
  )
VALUES
  (3, 1, 0, 'O', 0, 0);
-- --------------------------------------------------------
  --
  -- Table structure for table `log`
  --
  CREATE TABLE `log` (
    `log_timestamp` timestamp NOT NULL DEFAULT current_timestamp(),
    `log_type` enum('error', 'warning', 'info') NOT NULL DEFAULT 'info',
    `log_content` longtext NOT NULL
  ) ENGINE = InnoDB DEFAULT CHARSET = utf8mb4;
--
  -- Dumping data for table `log`
  --
INSERT INTO
  `log` (`log_timestamp`, `log_type`, `log_content`)
VALUES
  ('2021-11-20 10:26:38', 'info', 'dummy log');
-- --------------------------------------------------------
  --
  -- Table structure for table `schedule`
  --
  CREATE TABLE `schedule` (
    `schedule_id` int(11) NOT NULL PRIMARY KEY AUTO_INCREMENT,
    `subject_id` varchar(7) NOT NULL,
    `schedule_name` varchar(63) DEFAULT NULL,
    `schedule_start` timestamp NULL DEFAULT NULL,
    `schedule_end` timestamp NULL DEFAULT NULL
  ) ENGINE = InnoDB DEFAULT CHARSET = utf8mb4;
--
  -- Dumping data for table `schedule`
  --
INSERT INTO
  `schedule` (
    `schedule_id`,
    `subject_id`,
    `schedule_name`,
    `schedule_start`,
    `schedule_end`
  )
VALUES
  (
    1,
    'TSE2101',
    'Mid Term Exam',
    '2021-11-25 07:56:39',
    '2021-11-26 07:56:39'
  );
-- --------------------------------------------------------
  --
  -- Table structure for table `subject`
  --
  CREATE TABLE `subject` (
    `subject_id` varchar(7) NOT NULL,
    `course_id` varchar(7) NOT NULL,
    `subject_name` varchar(63) NOT NULL
  ) ENGINE = InnoDB DEFAULT CHARSET = utf8mb4;
--
  -- Dumping data for table `subject`
  --
INSERT INTO
  `subject` (`subject_id`, `course_id`, `subject_name`)
VALUES
  ('PMT0101', 'FIT', 'Mathematics I'),
  (
    'TCP2451',
    'BCS',
    'Programming Language Translation'
  ),
  ('TIS1101', 'BCS', 'Database Fundamentals'),
  ('TIS2151', 'BCS', 'Web Development Fundamentals'),
  (
    'TSE2101',
    'BCS',
    'Introduction to Software Engineering'
  ),
  ('TSN3251', 'BOE', 'Computer Security');
-- --------------------------------------------------------
  --
  -- Table structure for table `user`
  --
  CREATE TABLE `user` (
    `user_id` int(11) NOT NULL,
    `user_name` varchar(15) NOT NULL,
    `user_password` varchar(31) NOT NULL,
    `user_role` varchar(15) NOT NULL DEFAULT 'student',
    `user_email` varchar(63) NOT NULL,
    `user_fname` varchar(31) NOT NULL,
    `user_lname` varchar(31) NOT NULL,
    `user_phone` varchar(15) NOT NULL
  ) ENGINE = InnoDB DEFAULT CHARSET = utf8mb4;
--
  -- Dumping data for table `user`
  --
--
  -- Indexes for dumped tables
  --
  --
  -- Indexes for table `course`
  --
ALTER TABLE
  `course`
ADD
  PRIMARY KEY (`course_id`);
--
  -- Indexes for table `enrollment`
  --
ALTER TABLE
  `enrollment`
ADD
  PRIMARY KEY (`user_id`, `subject_id`),
ADD
  KEY `enrollment_ibfk_2` (`subject_id`),
ADD
  KEY `enrollment_ibfk_3` (`course_id`);
--
  -- Indexes for table `exam_answer`
  --
ALTER TABLE
  `exam_answer`
ADD
  PRIMARY KEY (`user_id`, `choice_id`),
ADD
  KEY `exam_answer_ibfk_2` (`question_id`),
ADD
  KEY `exam_answer_ibfk_3` (`choice_id`);
--
  -- Indexes for table `exam_choice`
  --
ALTER TABLE
  `exam_choice`
ADD
  PRIMARY KEY (`choice_id`),
ADD
  KEY `exam_choice_ibfk_1` (`question_id`);
--
  -- Indexes for table `exam_question`
  --
ALTER TABLE
  `exam_question`
ADD
  PRIMARY KEY (`question_id`),
ADD
  KEY `exam_question_ibfk_1` (`schedule_id`);
--
  -- Indexes for table `grade`
  --
ALTER TABLE
  `grade`
ADD
  PRIMARY KEY (`user_id`, `schedule_id`),
ADD
  KEY `grade_ibfk_2` (`schedule_id`);
--
  -- Indexes for table `schedule`
  --
ALTER TABLE
  `schedule`
ADD
  KEY `schedule_ibfk_1` (`subject_id`);
--
  -- Indexes for table `subject`
  --
ALTER TABLE
  `subject`
ADD
  PRIMARY KEY (`subject_id`),
ADD
  KEY `subject_ibfk_1` (`course_id`);
--
  -- Indexes for table `user`
  --
ALTER TABLE
  `user`
ADD
  PRIMARY KEY (`user_id`);
--
  -- AUTO_INCREMENT for dumped tables
  --
  --
  -- AUTO_INCREMENT for table `exam_choice`
  --
ALTER TABLE
  `exam_choice`
MODIFY
  `choice_id` int(11) NOT NULL AUTO_INCREMENT,
  AUTO_INCREMENT = 5;
--
  -- AUTO_INCREMENT for table `exam_question`
  --
ALTER TABLE
  `exam_question`
MODIFY
  `question_id` int(11) NOT NULL AUTO_INCREMENT,
  AUTO_INCREMENT = 2;
--
  -- AUTO_INCREMENT for table `user`
  --
ALTER TABLE
  `user`
MODIFY
  `user_id` int(11) NOT NULL AUTO_INCREMENT,
  AUTO_INCREMENT = 8;
--
  -- Constraints for dumped tables
  --
  --
  -- Constraints for table `enrollment`
  --
ALTER TABLE
  `enrollment`
ADD
  CONSTRAINT `enrollment_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`),
ADD
  CONSTRAINT `enrollment_ibfk_2` FOREIGN KEY (`subject_id`) REFERENCES `subject` (`subject_id`),
ADD
  CONSTRAINT `enrollment_ibfk_3` FOREIGN KEY (`course_id`) REFERENCES `course` (`course_id`);
--
  -- Constraints for table `exam_answer`
  --
ALTER TABLE
  `exam_answer`
ADD
  CONSTRAINT `exam_answer_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`),
ADD
  CONSTRAINT `exam_answer_ibfk_2` FOREIGN KEY (`question_id`) REFERENCES `exam_question` (`question_id`),
ADD
  CONSTRAINT `exam_answer_ibfk_3` FOREIGN KEY (`choice_id`) REFERENCES `exam_choice` (`choice_id`);
--
  -- Constraints for table `exam_choice`
  --
ALTER TABLE
  `exam_choice`
ADD
  CONSTRAINT `exam_choice_ibfk_1` FOREIGN KEY (`question_id`) REFERENCES `exam_question` (`question_id`);
--
  -- Constraints for table `exam_question`
  --
ALTER TABLE
  `exam_question`
ADD
  CONSTRAINT `exam_question_ibfk_1` FOREIGN KEY (`schedule_id`) REFERENCES `schedule` (`schedule_id`);
--
  -- Constraints for table `grade`
  --
ALTER TABLE
  `grade`
ADD
  CONSTRAINT `grade_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`),
ADD
  CONSTRAINT `grade_ibfk_2` FOREIGN KEY (`schedule_id`) REFERENCES `schedule` (`schedule_id`);
--
  -- Constraints for table `schedule`
  --
ALTER TABLE
  `schedule`
ADD
  CONSTRAINT `schedule_ibfk_1` FOREIGN KEY (`subject_id`) REFERENCES `subject` (`subject_id`);
--
  -- Constraints for table `subject`
  --
ALTER TABLE
  `subject`
ADD
  CONSTRAINT `subject_ibfk_1` FOREIGN KEY (`course_id`) REFERENCES `course` (`course_id`);
COMMIT;
  /*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
  /*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
  /*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;