/*create table if not exists selectcourse (
	sno int not null comment '学生号',
	cno int not null comment '课程号',
    grade int not null default 0 comment '学生成绩',
    
    primary key (sno, cno),
    foreign key selectcourse(sno) references student(sno),
    foreign key selectcourse(cno) references course(cno)
    );
*/

-- alter table student change column sname sname char(200) not null ;
-- alter table course change column cname cname char(200) not null;

/*
从选课表中选择学生都选择的一门课
*/
select teacher from course ;
select cno, cname from course where not exists (
	select * from student where not exists (
		select * from selectcourse where
        sno = student.sno and cno = course.cno));

/*
给没有选2001课程的选择，都选上2001课程，并给上默认成绩88
*/        
insert into selectcourse(sno, cno, grade) 
	select student.sno, 2001, 88 from student where student.sno not in ( 
    select selectcourse.sno from selectcourse where cno = 2001);

/*
查询所有选择课程2001的学生的总数目
*/
select distinct count(student.sno) from student 
	join selectcourse on student.sno = selectcourse.sno 
	where selectcourse.cno = 2001 ;

/*
从选课表中选择学生都选择的一门课
*/    
select course.cno, course.cname from course where 
	(select count(*) from selectcourse 
    where selectcourse.cno = course.cno) = ( select count(*) from student)
