#include "ImgRecognition.h"

int main()
{
	ImgRecognition ir;
	ir.initImage("image.jpg");
	ir.initParams();
	ir.initClases("base.jpg","class1.jpg","class2.jpg");
	ir.calcNearClasses();
	ir.calcRadiusClasses();
	ir.exam();
	ir.printResultFile();
		
	return 0;
}