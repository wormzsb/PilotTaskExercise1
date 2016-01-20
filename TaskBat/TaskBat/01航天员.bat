@echo off
@rem [TesterInfo]
@rem 编号	01
@rem 姓名	01
@rem 性别	男
@rem 年龄	44
@rem 第N次	0

@rem [Hardware]
@rem JoySpeedMax	300.00
@rem KnobSensitive	500.00
@rem DistanceError	10.00
@rem AngleError	10.00
@rem AngleError	10.00

@rem [TaskOrder]
@rem Task1
@rem Task1
@rem Task1
@rem Task1
@rem Task3_1
@rem Task3_1
@rem Task3_1
@rem Task3_1
@rem Task3_1
@rem Task3_1
@rem 
@rem [Task1(任务1-T1_1(跟踪50))]
@rem TaskName	任务1-T1_1(跟踪50)
@rem PracMode	0
@rem ExperMode	1
@rem Background	0
@rem Track	0
@rem Direction	0
@rem MoveMode	0
@rem SpeedMode	0
@rem Pause	0
@rem PauseNum	-1
@rem Speed	50.00
@rem InitSpeed	-1.00
@rem SpeedMin	-1.00
@rem SpeedMax	-1.00
@rem AccelerationMin	-1.00
@rem AccelerationMax	-1.00
@rem AngleSpeedMin	-1.00
@rem AngleSpeedMax	-1.00
@rem RotateAngleMin	-1.00
@rem RotateAngleMax	-1.00
@rem PracTime	-1
@rem ExperTime	120
@rem PracTimes	-1
@rem ExperTimes	1
@rem 
@rem [Task1(任务2-T1_2(跟踪100))]
@rem TaskName	任务2-T1_2(跟踪100)
@rem PracMode	0
@rem ExperMode	1
@rem Background	0
@rem Track	0
@rem Direction	0
@rem MoveMode	0
@rem SpeedMode	0
@rem Pause	0
@rem PauseNum	-1
@rem Speed	100.00
@rem InitSpeed	-1.00
@rem SpeedMin	-1.00
@rem SpeedMax	-1.00
@rem AccelerationMin	-1.00
@rem AccelerationMax	-1.00
@rem AngleSpeedMin	-1.00
@rem AngleSpeedMax	-1.00
@rem RotateAngleMin	-1.00
@rem RotateAngleMax	-1.00
@rem PracTime	-1
@rem ExperTime	90
@rem PracTimes	-1
@rem ExperTimes	1
@rem 
@rem [Task1(任务3-T1_3(跟踪150）)]
@rem TaskName	任务3-T1_3(跟踪150）
@rem PracMode	0
@rem ExperMode	1
@rem Background	0
@rem Track	0
@rem Direction	0
@rem MoveMode	0
@rem SpeedMode	0
@rem Pause	0
@rem PauseNum	-1
@rem Speed	150.00
@rem InitSpeed	-1.00
@rem SpeedMin	-1.00
@rem SpeedMax	-1.00
@rem AccelerationMin	-1.00
@rem AccelerationMax	-1.00
@rem AngleSpeedMin	-1.00
@rem AngleSpeedMax	-1.00
@rem RotateAngleMin	-1.00
@rem RotateAngleMax	-1.00
@rem PracTime	-1
@rem ExperTime	90
@rem PracTimes	-1
@rem ExperTimes	1
@rem 
@rem [Task1(任务4-T1_4(跟踪200))]
@rem TaskName	任务4-T1_4(跟踪200)
@rem PracMode	0
@rem ExperMode	1
@rem Background	0
@rem Track	0
@rem Direction	0
@rem MoveMode	0
@rem SpeedMode	0
@rem Pause	0
@rem PauseNum	-1
@rem Speed	200.00
@rem InitSpeed	-1.00
@rem SpeedMin	-1.00
@rem SpeedMax	-1.00
@rem AccelerationMin	-1.00
@rem AccelerationMax	-1.00
@rem AngleSpeedMin	-1.00
@rem AngleSpeedMax	-1.00
@rem RotateAngleMin	-1.00
@rem RotateAngleMax	-1.00
@rem PracTime	-1
@rem ExperTime	90
@rem PracTimes	-1
@rem ExperTimes	1
@rem 
@rem [Task3(任务5-T3_1(简单))]
@rem TaskName	任务5-T3_1(简单)
@rem PracMode	0
@rem ExperMode	1
@rem MainTask	0
@rem SubTask	1
@rem MainTaskMode	-1
@rem Background	0
@rem InitSpeed	-1.00
@rem EventMode	0
@rem CodePairMode	-1
@rem CodePairNum	-1
@rem DisplayMode	-1
@rem EventFrequency	15
@rem PracTime	-1
@rem ExperTime	60
@rem PracTimes	1
@rem ExperTimes	1
@rem 
@rem [Task3(任务6-T3_2(选择))]
@rem TaskName	任务6-T3_2(选择)
@rem PracMode	0
@rem ExperMode	1
@rem MainTask	0
@rem SubTask	1
@rem MainTaskMode	-1
@rem Background	0
@rem InitSpeed	-1.00
@rem EventMode	1
@rem CodePairMode	-1
@rem CodePairNum	-1
@rem DisplayMode	-1
@rem EventFrequency	15
@rem PracTime	-1
@rem ExperTime	90
@rem PracTimes	1
@rem ExperTimes	1
@rem 
@rem [Task3(任务7-T3_3(跟踪50+简单))]
@rem TaskName	任务7-T3_3(跟踪50+简单)
@rem PracMode	0
@rem ExperMode	1
@rem MainTask	1
@rem SubTask	1
@rem MainTaskMode	0
@rem Background	0
@rem InitSpeed	50.00
@rem EventMode	0
@rem CodePairMode	-1
@rem CodePairNum	-1
@rem DisplayMode	-1
@rem EventFrequency	15
@rem PracTime	-1
@rem ExperTime	90
@rem PracTimes	1
@rem ExperTimes	1
@rem 
@rem [Task3(任务8-T3_4(跟踪50+选择))]
@rem TaskName	任务8-T3_4(跟踪50+选择)
@rem PracMode	0
@rem ExperMode	1
@rem MainTask	1
@rem SubTask	1
@rem MainTaskMode	0
@rem Background	0
@rem InitSpeed	50.00
@rem EventMode	1
@rem CodePairMode	-1
@rem CodePairNum	-1
@rem DisplayMode	-1
@rem EventFrequency	15
@rem PracTime	-1
@rem ExperTime	120
@rem PracTimes	1
@rem ExperTimes	1
@rem 
@rem [Task3(任务9-T3_5(跟踪100+简单))]
@rem TaskName	任务9-T3_5(跟踪100+简单)
@rem PracMode	0
@rem ExperMode	1
@rem MainTask	1
@rem SubTask	1
@rem MainTaskMode	0
@rem Background	0
@rem InitSpeed	100.00
@rem EventMode	0
@rem CodePairMode	-1
@rem CodePairNum	-1
@rem DisplayMode	-1
@rem EventFrequency	15
@rem PracTime	-1
@rem ExperTime	90
@rem PracTimes	1
@rem ExperTimes	1
@rem 
@rem [Task3(任务10-T3_6(跟踪100+选择))]
@rem TaskName	任务10-T3_6(跟踪100+选择)
@rem PracMode	0
@rem ExperMode	1
@rem MainTask	1
@rem SubTask	1
@rem MainTaskMode	0
@rem Background	0
@rem InitSpeed	100.00
@rem EventMode	1
@rem CodePairMode	-1
@rem CodePairNum	-1
@rem DisplayMode	-1
@rem EventFrequency	15
@rem PracTime	-1
@rem ExperTime	120
@rem PracTimes	1
@rem ExperTimes	1
@rem 
@rem 
@TaskBat.exe 01航天员.bat