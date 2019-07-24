// File name: main.cpp
// Author: Viet Than
// Email: viet.than@vanderbilt.edu (thanhoangviet@gmail.com)
// Lab: Medical Imaging Lab under Ipek Oguz
// Description: implementing a Hessian-based filter for vessel-enhancement in images



#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkExtractImageFilter.h"

#include "itkHessianToObjectnessMeasureImageFilter.h"
#include "itkMultiScaleHessianBasedMeasureImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

#include <string>
#include <iostream>
#include <chrono>
#include <iomanip> //set precision
#include <sstream> //stringstream

using namespace itk;

//helper functions
std::string makeInputFileName (const std::string &filename, const std::string &filetype);
std::string makeOutputFileName (const std::string &filename, const std::string &filetype, 
				const float &alpha, const float &beta, const float &gamma, 
				const double &min, const double &max, const unsigned int &step);


template <typename T> std::string returnPointString(const T &number);

// 5 arguments:
// 1 - filename
// 2 - filetype
// 3 - alpha
// 4 - beta
// 5 - gamma
// 6 - min
// 7 - max
// 8 - step
int main(int argc, char * argv []){
	std::cout << "Starting Hessian filter" << std::endl;

	if (argc > 9){
		std::cout << "too many arguments" << std::endl;
		return EXIT_FAILURE;
	}

	// setting up arguments
	std::string filename, filetype;
	float alpha, beta, gamma;
	double sigmaMinimum, sigmaMaximum;
	unsigned int numberOfSigmaSteps;
	// constexpr, computation at compile time
	constexpr unsigned int Dimension = 3;
	constexpr float desiredMinimum = 0.0;
	constexpr float desiredMaximum = 255.0;
	
	if (argc == 9){
		filename = argv[1];
		filetype = argv[2];
		alpha = std::stof(argv[3]);
		beta = std::stof(argv[4]);
		gamma = std::stof(argv[5]);
		sigmaMinimum = std::atof(argv[6]);
		sigmaMaximum = std::atof(argv[7]);
		numberOfSigmaSteps = atoi(argv[8]);
	} else {
		std::cout << "Not enough arguments, went with default" << std::endl;
		filename = "Smallfield_OCT_Angiography_Volume_fovea"; //filename in data/
		filetype = ".nii";
		alpha = 0.8;
		beta = 1;
		gamma = 250;
		sigmaMinimum = 0.5;
		sigmaMaximum = 12;
		numberOfSigmaSteps = 11;
	}

	//timing
	auto start = std::chrono::high_resolution_clock::now();	

	std::string inputFileName = makeInputFileName(filename, filetype);
	
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " milliseconds for reading in the file and creating constants"<<std::endl;


  	
	std::string outputFileName = makeOutputFileName(filename, filetype, alpha, beta, gamma, sigmaMinimum, sigmaMaximum, numberOfSigmaSteps);


	//Setting up the image reader of the particular type
	using PixelType = float;
  	using ImageType = itk::Image< PixelType, Dimension >;
  	using ReaderType = itk::ImageFileReader< ImageType >;

	//Setting up the reader
  	ReaderType::Pointer reader = ReaderType::New();
  	reader->SetFileName( inputFileName );
  	reader->Update();

 	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " milliseconds for setting image and reader"<<std::endl;

	ImageType::Pointer image = reader->GetOutput();
	ImageType::RegionType region = image->GetLargestPossibleRegion();
	ImageType::SizeType size = region.GetSize();


  	using HessianPixelType = itk::SymmetricSecondRankTensor< float, Dimension >;
  	using HessianImageType = itk::Image< HessianPixelType, Dimension >;
  	using ObjectnessFilterType = itk::HessianToObjectnessMeasureImageFilter< HessianImageType, ImageType >;
  	ObjectnessFilterType::Pointer objectnessFilter = ObjectnessFilterType::New();
  	objectnessFilter->SetBrightObject( true );
  	objectnessFilter->SetScaleObjectnessMeasure( false );
  	objectnessFilter->SetAlpha( alpha );
  	objectnessFilter->SetBeta( beta );
  	objectnessFilter->SetGamma( gamma );

 	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " milliseconds for setting Hessian output image"<<std::endl;


  	using MultiScaleEnhancementFilterType = itk::MultiScaleHessianBasedMeasureImageFilter< ImageType, HessianImageType, ImageType >;
  	MultiScaleEnhancementFilterType::Pointer multiScaleEnhancementFilter = MultiScaleEnhancementFilterType::New();
  	multiScaleEnhancementFilter->SetInput( reader->GetOutput() );
  	multiScaleEnhancementFilter->SetHessianToMeasureFilter( objectnessFilter );
  	multiScaleEnhancementFilter->SetSigmaStepMethodToLogarithmic();
  	multiScaleEnhancementFilter->SetSigmaMinimum( sigmaMinimum );
  	multiScaleEnhancementFilter->SetSigmaMaximum( sigmaMaximum );
  	multiScaleEnhancementFilter->SetNumberOfSigmaSteps( numberOfSigmaSteps );

 	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " milliseconds for setting up the Hessian filter" <<std::endl;

	//
  	using OutputImageType = itk::Image< float, Dimension >;
  	using RescaleFilterType = itk::RescaleIntensityImageFilter< ImageType, OutputImageType >;
  	RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
  	rescaleFilter->SetInput( multiScaleEnhancementFilter->GetOutput() );
	
	//rescale to 0 and 255 for output
	rescaleFilter->SetOutputMinimum(desiredMinimum);
	rescaleFilter->SetOutputMaximum(desiredMaximum);

 	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " milliseconds for setting min max intensity"<< std::endl;

	//Setting up the output writer
  	using WriterType = itk::ImageFileWriter< OutputImageType >;//setting up type for writer
  	WriterType::Pointer writer = WriterType::New();//initialize new writer pointer
  	writer->SetFileName( outputFileName );//set filename for writer
  	writer->SetInput( rescaleFilter->GetOutput() );//
	//writer->SetUseCompression( true );
	
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " milliseconds for setting up writer" << std::endl;


	//Write to file
  	try {
    	writer->Update();
    	} catch ( itk::ExceptionObject & error ){
    	std::cerr << "Error: " << error << std::endl;
    	return EXIT_FAILURE;
    	}
	
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " milliseconds when " << outputFileName << " written out succesfully" << std::endl;
  	return EXIT_SUCCESS;
	

}

//Creating the input file name for a nifti
std::string makeInputFileName (const std::string &filename, const std::string &filetype){
	std::string inputFileName = "../data/";
	inputFileName.append(filename);
	inputFileName.append(filetype);
	return inputFileName;
}

//Creating the output filename for a nifti
std::string makeOutputFileName  (const std::string &filename, const std::string &filetype, 
				const float &alpha, const float &beta, const float &gamma, 
				const double &min, const double &max, const unsigned int &step){
	std::string OutputFileName = "../output/";
	OutputFileName.append(filename);
	OutputFileName.append("_Hessian");
	OutputFileName.append("_");
	OutputFileName.append(returnPointString(alpha));
	OutputFileName.append("_");
	OutputFileName.append(returnPointString(beta));
	OutputFileName.append("_");
	OutputFileName.append(returnPointString(gamma));
	OutputFileName.append("_");
	OutputFileName.append(returnPointString(min));
	OutputFileName.append("_");
	OutputFileName.append(returnPointString(max));
	OutputFileName.append("_");
	OutputFileName.append(std::to_string(step));
	OutputFileName.append(filetype);
	return OutputFileName;
}

template <typename T> std::string returnPointString(const T &number){
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << number;
    std::string s = stream.str();

    s.replace(s.find('.'), 1, "p");
    return s;
}


