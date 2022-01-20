//
//  ViewController.swift
//
//  Created by Fernando Mujica on 11/21/17.
//  Copyright © 2017 Stanford University. All rights reserved.
//

import UIKit

class MainViewController: UIViewController, UIPickerViewDataSource, UIPickerViewDelegate {
    
    var audioFilesArray = ["Select an audio file..."]

    let audioFileURLsArray : [URL] = Bundle.main.urls(forResourcesWithExtension: "caf", subdirectory: ".")!
    
    var selectedAudioFileURL : URL? = nil
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return audioFilesArray.count
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return audioFilesArray[row]
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {

        if row > 0 {
            selectedAudioFileURL = audioFileURLsArray[row - 1]
        } else {
            selectedAudioFileURL = nil
        }
        print("Selected row: \(row)  audio file: \(audioFilesArray[row])")
    }
    
    // Dismiss keyboard
    // https://medium.com/@KaushElsewhere/how-to-dismiss-keyboard-in-a-view-controller-of-ios-3b1bfe973ad1
    override func touchesBegan(_ touches: Set<UITouch>,
                               with event: UIEvent?) {
        self.view.endEditing(true)
    }

    @IBOutlet weak var outputSamplingRateTextField: UITextField!
    
    @IBAction func outputSamplingRateTextField(_ sender: UITextField) {

    }
    
    @IBOutlet weak var outputPreferredNumFramesTextField: UITextField!
    
    @IBAction func ioBufferDurationTextField(_ sender: Any) {
        
        updateFileBlockSize()
    }
    
    @IBOutlet weak var audioFileUpSampleFactorTextField: UITextField!
    
    @IBAction func fileUpSampleRatioTextField(_ sender: UITextField) {
        
        updateFileBlockSize()
    }
    
    @IBOutlet weak var audioFileDownSampleFactorTextField: UITextField!
    
    @IBAction func fileDownSampleRatioTextField(_ sender: UITextField) {
        
        updateFileBlockSize()
    }
    
    @IBOutlet weak var FileBlockSizeTextField: UITextField!
    
    @IBOutlet weak var audioFilePicker: UIPickerView!
    
    @IBOutlet weak var testButton: UIButton!
    
    @IBAction func testButton(_ sender: UIButton) {
        
        print("Test button pressed!")
        print("Mode: \(String(describing: Int(modeTextField.text!)))")
        audioController.testFlag = true
        audioController.mode = Int(modeTextField.text!)!
    }
    
    @IBOutlet weak var modeTextField: UITextField!
    
    @IBAction func modeTextField(_ sender: UITextField) {
    }
    
    @IBOutlet weak var startSwitch: UISwitch!
    
    @IBAction func startSwitch(_ sender: UISwitch) {
        if sender.isOn {
            // Disable parameter input
            outputSamplingRateTextField.isEnabled = false
            outputPreferredNumFramesTextField.isEnabled = false
            audioFileUpSampleFactorTextField.isEnabled = false
            audioFileDownSampleFactorTextField.isEnabled = false
            
            // Clear buffers
            audioController.clearBuffers()
            
            // Set mode
            audioController.mode = Int(modeTextField.text!)!
            
            // Update parameters from UI
            audioController.preferredSpeakerSampleRate = Double(outputSamplingRateTextField.text!)!
            audioController.preferredSpeakerNumSamples = Int(outputPreferredNumFramesTextField.text!)!
            audioController.audioFileUpSampleFactor = Int(audioFileUpSampleFactorTextField.text!)!
            audioController.audioFileDownSampleFactor = Int(audioFileDownSampleFactorTextField.text!)!
            audioController.audioFileURL = selectedAudioFileURL
            
            // Call C++ setup funtion
            AudioProcessingSetupWrapper().setup(
                Int32(audioController.preferredSpeakerNumSamples),
                upSampleFactor: Int32(audioController.audioFileUpSampleFactor),
                downSampleFactor: Int32(audioController.audioFileDownSampleFactor))
            
            // Enable sound
            audioController.setupAudioChain()
            audioController.startIOUnit()
            
            if (audioController.preferredSpeakerNumSamples != audioController.speakerNumSamples) {
                outputPreferredNumFramesTextField.text = String(format: "%d", audioController.speakerNumSamples)
                outputPreferredNumFramesTextField.textColor = UIColor.red
            }
            
            if (audioController.preferredSpeakerSampleRate != audioController.speakerSampleRate) {
                outputSamplingRateTextField.text = String(format: "%.f", audioController.speakerSampleRate)
                outputSamplingRateTextField.textColor = UIColor.red
            }
            
        } else {
            // Enable parameter input
            outputSamplingRateTextField.isEnabled = true
            outputPreferredNumFramesTextField.isEnabled = true
            audioFileUpSampleFactorTextField.isEnabled = true
            audioFileDownSampleFactorTextField.isEnabled = true
            
            if (audioController.preferredSpeakerNumSamples != audioController.speakerNumSamples) {
                outputPreferredNumFramesTextField.text = String(format: "%d", audioController.preferredSpeakerNumSamples)
                outputPreferredNumFramesTextField.textColor = UIColor.black
            }
            
            if (audioController.preferredSpeakerSampleRate != audioController.speakerSampleRate) {
                outputSamplingRateTextField.text = String(format: "%.f", audioController.preferredSpeakerSampleRate)
                outputSamplingRateTextField.textColor = UIColor.black
            }
            
            // Disable sound
            audioController.stopIOUnit()
            audioController.deactivateAudioSession()

            // Call C++ cleanup funtion
            AudioProcessingCleanupWrapper().cleanup()            
        }
        updateFileBlockSize()
    }
    
    @IBAction func micOnSwitch(_ sender: UISwitch) {
        if sender.isOn {
            audioController.micOn = true
        } else {
            audioController.micOn = false
        }
    }
    
    @IBAction func speakerOnSwitch(_ sender: UISwitch) {
        if sender.isOn {
            audioController.speakerOn = true
        } else {
            audioController.speakerOn = false
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        // UI designed for light mode
        overrideUserInterfaceStyle = .light
        
        print("\nMain view\n")
        updateFileBlockSize()
        
        print("File URLs")
        for url in audioFileURLsArray {
            print(url.lastPathComponent)
            audioFilesArray.append(url.lastPathComponent)
        }
        print(audioFilesArray)
        
        audioFilePicker.delegate = self
        audioFilePicker.dataSource = self
        audioFilePicker.selectRow(0, inComponent: 0, animated: false)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func updateFileBlockSize() {
        
        var fileBlockSize : Double
        if startSwitch.isOn {
            fileBlockSize = Double(audioController.speakerNumSamples) * Double(audioFileDownSampleFactorTextField.text!)! / Double(audioFileUpSampleFactorTextField.text!)!
        } else {
            fileBlockSize = Double(outputPreferredNumFramesTextField.text!)! * Double(audioFileDownSampleFactorTextField.text!)! / Double(audioFileUpSampleFactorTextField.text!)!
        }
        FileBlockSizeTextField.text = String(format: "%.02f", fileBlockSize)
        
        // Highlight non-integer average block size
        if fileBlockSize.remainder(dividingBy: 1.0) == 0.0 {
            FileBlockSizeTextField.textColor = UIColor.black

        } else {
            FileBlockSizeTextField.textColor = UIColor.red
        }

    }

}

