# Enhancing vessels in 3D images with Hessian/Frangi/Eigenvalue filter

<p align="left">
	<img src="https://img.shields.io/badge/platform-ubuntu-blueviolet?style=for-the-badge"
			 alt="platform">
	<img src="https://img.shields.io/badge/language-C++11-green?style=for-the-badge"
			 alt="language">
  	<img src="https://img.shields.io/badge/compiler-GCC 5.4.0-green?style=for-the-badge"
			 alt="compiler">
	<img src="https://img.shields.io/badge/builder-cmake 3.7.1-green?style=for-the-badge"
			 alt="builder">
	<img src="https://img.shields.io/badge/library-ITK 4.12.2|Python2.7.12-critical?style=for-the-badge"
			 alt="compiler">
</p>

Based on "Multiscale vessel enhancement filtering" by A.F. Frangi, 1998. <a href="https://link.springer.com/chapter/10.1007/BFb0056195">Link to paper</a>.<br>
Developed by Viet Than, Medical Image Computing Lab under Ipek Oguz, Vanderbilt University. 2019.

## ITK library
<i>"ITK is an open-source, cross-platform system that provides developers with an extensive suite of software tools for image analysis."</i><br>
 - developed by the National Library of Medicine
 
## Hessian filters
There should only be one but was separated into 2 parts, both is needed. One applies the Frangi equation on the eigenvalues extracted from the Hessian information of the image, the other applies the previous to different scale levels. Filters contributed by Luca Antiga of Medical Imaging Unit, Bioengineering Department, Mario Negri Institute, Italy.
 - itkHessianToObjectnessMeasureImageFilter.h
 - itkMultiScaleHessianBasedMeasureImageFilter.h
 
## Some notes on parameters
1. Alpha
2. Beta
3. Gamma
4. Sigma

## Data example
Smallfield fovea angiography provided by the Diagnostic Imaging and Image-Guided Interventions Lab under Yuankai Tao, Vanderbilt University. 2019.

## Author and Acknowledgements
Author: Viet Than, Department of EECS, Vanderbilt University, US.<br>
Supervisor: Ipek Oguz, Prof. Department of EECS, Vanderbilt University, US.

With the help of the Medical Image Computing Lab.
