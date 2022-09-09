#pragma once

enum CommandType
{
	Create,
	Edit,
	Read,
	Zip,
	Exit,
	Help
};

enum CommandContextType
{
	FilePath,
	FileType
};