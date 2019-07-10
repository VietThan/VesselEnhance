# Enhancing vessels in 3D images with Hessian/Frangi/Eigenvalue filter<br>
Based on "Multiscale vessel enhancement filtering" by A.F. Frangi, 1998.<br>
Developed by Viet Than, Medical Image Computing Lab under Ipek Oguz, Vanderbilt University. 2019.
## ITK library<br>
<i>"ITK is an open-source, cross-platform system that provides developers with an extensive suite of software tools for image analysis.</i><br>
 - developed by the National Library of Medicine<br>
## Hessian filters<br>
There should only be one but was separated into 2 parts, both is needed. One appies the Frangi equation on the eigenvalues extracted from the Hessian information of the image, the other applies the previous to different scale levels. Filters contributed by Luca Antiga of Medical Imaging Unit, Bioengineering Department, Mario Negri Institute, Italy.<br>
 - itkHessianToObjectnessMeasureImageFilter.h<br>
 - itkMultiScaleHessianBasedMeasureImageFilter.h<br>
## Data example<br>
Smallfield fovea angiography provided by the Diagnostic Imaging and Image-Guided Interventions Lab under Yuankai Tao, Vanderbilt University<br>
