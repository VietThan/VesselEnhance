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
std::string makeInputFileName (std::string &filename);
std::string makeOutputFileName (std::string &filename);


int main(){

	//timing
	auto start = std::chrono::high_resolution_clock::now();	

	// constexpr, computation at compile time
	constexpr unsigned int Dimension = 3;
	std::string filename = "Smallfield_OCT_Angiography_Volume_fovea";
	std::string inputFileName = makeInputFileName(filename);
	std::string outputFileName = makeOutputFileName(filename);

	//Creating the sigma/scales at which we're working at
	double sigmaMinimum = 1.0;
	double sigmaMaximum = 10.0;
	unsigned int numberOfSigmaSteps = 10;
  	

	//Setting up the image reader of the particular type
	using PixelType = float;
  	using ImageType = itk::Image< PixelType, Dimension >;
  	using ReaderType = itk::ImageFileReader< ImageType >;

	//
  	ReaderType::Pointer reader = ReaderType::New();
  	reader->SetFileName( inputFileName );
  	reader->Update();

  	using HessianPixelType = itk::SymmetricSecondRankTensor< double, Dimension >;
  	using HessianImageType = itk::Image< HessianPixelType, Dimension >;
  	using ObjectnessFilterType = itk::HessianToObjectnessMeasureImageFilter< HessianImageType, ImageType >;
  	ObjectnessFilterType::Pointer objectnessFilter = ObjectnessFilterType::New();
  	objectnessFilter->SetBrightObject( true );
  	objectnessFilter->SetScaleObjectnessMeasure( false );
  	objectnessFilter->SetAlpha( 0.5 );
  	objectnessFilter->SetBeta( 1.0 );
  	objectnessFilter->SetGamma( 5.0 );

  	using MultiScaleEnhancementFilterType = itk::MultiScaleHessianBasedMeasureImageFilter< ImageType, HessianImageType, ImageType >;
  	MultiScaleEnhancementFilterType::Pointer multiScaleEnhancementFilter = MultiScaleEnhancementFilterType::New();
  	multiScaleEnhancementFilter->SetInput( reader->GetOutput() );
  	multiScaleEnhancementFilter->SetHessianToMeasureFilter( objectnessFilter );
  	multiScaleEnhancementFilter->SetSigmaStepMethodToLogarithmic();
  	multiScaleEnhancementFilter->SetSigmaMinimum( sigmaMinimum );
  	multiScaleEnhancementFilter->SetSigmaMaximum( sigmaMaximum );
  	multiScaleEnhancementFilter->SetNumberOfSigmaSteps( numberOfSigmaSteps );

  	using OutputImageType = itk::Image< unsigned char, Dimension >;
  	using RescaleFilterType = itk::RescaleIntensityImageFilter< ImageType, OutputImageType >;
  	RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
  	rescaleFilter->SetInput( multiScaleEnhancementFilter->GetOutput() );

  	using WriterType = itk::ImageFileWriter< OutputImageType >;
  	WriterType::Pointer writer = WriterType::New();
  	writer->SetFileName( outputFileName );
  	writer->SetInput( rescaleFilter->GetOutput() );

  	try {
    	writer->Update();
    	} catch ( itk::ExceptionObject & error ){
    	std::cerr << "Error: " << error << std::endl;
    	return EXIT_FAILURE;
    	}
	
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << duration.count() <<std::endl;
	std::cout << "it works" << std::endl;
  	return EXIT_SUCCESS;
	

}

//Creating the input file name for a nifti
std::string makeInputFileName (std::string &filename){
	std::string inputFileName = "../data/";
	inputFileName.append(filename);
	inputFileName.append(".nii");
	return inputFileName;
}

//Creating the output filename for a nifti
std::string makeOutputFileName (std::string &filename){
	std::string OutputFileName = "../data/";
	OutputFileName.append(filename);
	OutputFileName.append("_Output.nii");
	return OutputFileName;

}
