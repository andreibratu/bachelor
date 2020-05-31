import React, {useEffect, useState} from 'react';
import './UploadPresentationModal.css';
import {FileUploader} from "baseui/file-uploader";
import {SIZE as INPUT_SIZE} from "baseui/input";
import {KIND as BUTTON_KIND} from 'baseui/button';
import {
    Modal,
    ModalBody,
    ModalButton,
    ModalFooter,
    ModalHeader,
    ROLE as MODAL_ROLE,
    SIZE as MODAL_SIZE
} from "baseui/modal";
import {useDispatch, useSelector} from "react-redux";
import {FILE_SUBMITTED_TOKEN} from "../../../constants";
import {FormControl} from "baseui/form-control";
import conferenceService from "../../../redux/conference/conferenceService";

const UploadPresentationModal = (props) => {
    const dispatch = useDispatch();
    const {modalOpen, setModalOpen, uploadPresentation} = props;

    // Context
    const contextProposal = useSelector(state => state.context.currentProposal);
    const currUserEmail = useSelector(state => state.auth.email);
    const proposalName = contextProposal?.proposalName;

    const [progressAmount, setProgressAmount] = useState(null);
    const [progressMessage, setProgressMessage] = useState('');



    const [formValid, setFormValid] = useState(true);
    let editScenario = contextProposal != null;


    const [presentationFile, setPresentationFile] = useState(
        contextProposal?.filePath ? FILE_SUBMITTED_TOKEN : null
    );

    useEffect( () => {
        setFormValid(presentationFile != null);
        }
    );

    return (
        <div className="UploadPresentationModal">
            <Modal
                onClose={() => setModalOpen(false)}
                isOpen={modalOpen}
                animate
                autoFocus
                size={MODAL_SIZE.default}
                role={MODAL_ROLE.default}
            >
                {!uploadPresentation && <ModalHeader>{`${proposalName} Proposal`}</ModalHeader>}
                <ModalBody>

                    <div className={'AddPresentationFormDiv'}>
                        {
                            <FormControl
                                label={'Presentation'}
                                caption={(presentationFile === FILE_SUBMITTED_TOKEN || uploadPresentation) ?
                                    'Your last submission has been registered'
                                    :
                                    ''
                                }>
                                <FileUploader
                                    onCancel={() => {
                                        setProgressAmount(null);
                                        setProgressMessage(null);
                                    }}
                                    onDrop={accepted => {
                                        let reader = new FileReader();
                                        reader.onload = () => {
                                            setPresentationFile(reader.result.slice(37));
                                        };
                                        reader.readAsDataURL(accepted[0]);
                                        setProgressAmount(100);
                                        setProgressMessage('Your presentation has been registered!')
                                    }}
                                    progressAmount={progressAmount}
                                    progressMessage={progressMessage}
                                />
                            </FormControl>
                        }

                        <ModalFooter>
                            <ModalButton
                                kind={BUTTON_KIND.secondary}
                                onClick={() => {
                                    props.setModalOpen(false);
                                }}
                                size={INPUT_SIZE.compact}>
                                Cancel
                            </ModalButton>
                            <ModalButton
                                size={INPUT_SIZE.compact}
                                disabled={!formValid}
                                onClick={() => {
                                    if (editScenario) {
                                        dispatch(conferenceService.addPresentation(
                                            contextProposal.id,
                                            currUserEmail, //presenter
                                            presentationFile === FILE_SUBMITTED_TOKEN ? null : presentationFile
                                        ))
                                    } else {
                                        dispatch(conferenceService.addPresentation(
                                            contextProposal.id,
                                            currUserEmail, //presenter
                                            presentationFile
                                        ));
                                    }
                                }}>
                                {editScenario ? 'Update' : 'Submit'}
                            </ModalButton>
                        </ModalFooter>
                    </div>
                </ModalBody>
            </Modal>
        </div>
    );
};

// import React from 'react';
// import './UploadPresentationModal.css';
//
// const UploadPresentationModal = () => (
//     <div className="UploadPresentationModal">
//         UploadPresentationModal Component
//     </div>
// );

UploadPresentationModal.propTypes = {};

UploadPresentationModal.defaultProps = {};

export default UploadPresentationModal;
