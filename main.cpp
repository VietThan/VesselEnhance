// File name: main.cpp
// Author: Viet Than
// Email: viet.than@vanderbilt.edu (thanhoangviet@gmail.com)
// Lab: Medical Imaging Lab under Ipek Oguz
// Description: implementing a Hessian-based filter for vessel-enhancement in images



#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkHessianToObjectnessMeasureImageFilter.h"
#include "itkMultiScaleHessianBasedMeasureImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

#include <string>
#include <iostream>
#include <chrono>


using namespace itk;

//helper functions
std::string makeInputFileName (std::string &filename, std::string &filetype);
std::string makeOutputFileName (std::string &filename, std::string &filetype);


// 5 arguments:
// filename
// filetype
// alpha
// beta
// gamma
int main(int argc, char * argv []){

	if (argc > 5){
		std::cout << "too many arguments" << std::endl;
		return EXIT_FAILURE;
	}

	// setting up arguments
	std::string filename, filetype;
	float alpha, beta, gamma;

	constexpr unsigned int Dimension = 3;
	
	if (argc == 5){
		filename = argv[0];
		filetype = argv[1];
		alpha = std::stof(argv[2]);
		beta = std::stof(argv[3]);
		gamma = std::stof(argv[4]);
	} else {
		std::cout << "Not enough arguments, went with default" << std::endl;
		filename = "Smallfield_OCT_Angiography_Volume_fovea"; //filename in data/
		filetype = ".nii";
		alpha = 0.1;
		beta = 8.0;
		gamma = 250;
	}

	//timing
	auto start = std::chrono::high_resolution_clock::now();	

	// constexpr, computation at compile time
	std::string inputFileName = makeInputFileName(filename, filetype);
	std::string outputFileName = makeOutputFileName(filename, filetype);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << duration.count() << " reading in the file"<<std::endl;


	//Creating the sigma/scales at which we're working at
	double sigmaMinimum = 0.1;
	double sigmaMaximum = 8;
	unsigned int numberOfSigmaSteps = 10;
  	
 	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << duration.count() << " Creating constants"<<std::endl;


	//Setting up the image reader of the particular type
	using PixelType = float;
  	using ImageType = itk::Image< PixelType, Dimension >;
  	using ReaderType = itk::ImageFileReader< ImageType >;

	//Setting up the reader
  	ReaderType::Pointer reader = ReaderType::New();
  	reader->SetFileName( inputFileName );
  	reader->Update();

 	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << duration.count() << " setting image and reader"<<std::endl;

  	using HessianPixelType = itk::SymmetricSecondRankTensor< double, Dimension >;
  	using HessianImageType = itk::Image< HessianPixelType, Dimension >;
  	using ObjectnessFilterType = itk::HessianToObjectnessMeasureImageFilter< HessianImageType, ImageType >;
  	ObjectnessFilterType::Pointer objectnessFilter = ObjectnessFilterType::New();
  	objectnessFilter->SetBrightObject( true );
  	objectnessFilter->SetScaleObjectnessMeasure( false );
  	objectnessFilter->SetAlpha( alpha );
  	objectnessFilter->SetBeta( beta );
  	objectnessFilter->SetGamma( gamma );

 	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << duration.count() << " Setting Hessian output image"<<std::endl;


  	using MultiScaleEnhancementFilterType = itk::MultiScaleHessianBasedMeasureImageFilter< ImageType, HessianImageType, ImageType >;
  	MultiScaleEnhancementFilterType::Pointer multiScaleEnhancementFilter = MultiScaleEnhancementFilterType::New();
  	multiScaleEnhancementFilter->SetInput( reader->GetOutput() );
  	multiScaleEnhancementFilter->SetHessianToMeasureFilter( objectnessFilter );
  	multiScaleEnhancementFilter->SetSigmaStepMethodToLogarithmic();
  	multiScaleEnhancementFilter->SetSigmaMinimum( sigmaMinimum );
  	multiScaleEnhancementFilter->SetSigmaMaximum( sigmaMaximum );
  	multiScaleEnhancementFilter->SetNumberOfSigmaSteps( numberOfSigmaSteps );

 	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << duration.count() << " Setting up the Hessian filter" <<std::endl;

	//
  	using OutputImageType = itk::Image< float, Dimension >;
  	using RescaleFilterType = itk::RescaleIntensityImageFilter< ImageType, OutputImageType >;
  	RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
  	rescaleFilter->SetInput( multiScaleEnhancementFilter->GetOutput() );

 	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << duration.count() << " Get the output"<< std::endl;

	//Setting up the output writer
  	using WriterType = itk::ImageFileWriter< OutputImageType >;//setting up type for writer
  	WriterType::Pointer writer = WriterType::New();//initialize new writer pointer
  	writer->SetFileName( outputFileName );//set filename for writer
  	writer->SetInput( rescaleFilter->GetOutput() );//
	
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << duration.count() << " writer set" << std::endl;
  	
	//Write to file
  	try {
    	writer->Update();
    	} catch ( itk::ExceptionObject & error ){
    	std::cerr << "Error: " << error << std::endl;
    	return EXIT_FAILURE;
    	}
	
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << duration.count() <<std::endl;
	std::cout << "File written out succesfully" << std::endl;
  	return EXIT_SUCCESS;
	

}

//Creating the input file name for a nifti
std::string makeInputFileName (std::string &filename, std::string &filetype){
	std::string inputFileName = "../data/";
	inputFileName.append(filename);
	inputFileName.append(filetype);
	return inputFileName;
}

//Creating the output filename for a nifti
std::string makeOutputFileName (std::string &filename, std::string &filetype){
	std::string OutputFileName = "../data/";
	OutputFileName.append(filename);
	OutputFileName.append("_Output");
	OutputFileName.append(filetype);
	return OutputFileName;

}
