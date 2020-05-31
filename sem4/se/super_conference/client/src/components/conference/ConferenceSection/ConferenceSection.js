import React, {useState} from 'react';
import './ConferenceSection.css';
import SectionNavigation from "../../navigation/SectionNavigation/SectionNavigation";
import NotFound from "../../navigation/NotFound/NotFound";
import {Route, Switch} from "react-router-dom";
import ListContainer from "../../generic/ListContainer/ListContainer";
import {RESET_CONTEXT_PROPOSAL} from "../../../redux/context/contextActions";
import {Button, KIND as BUTTON_KIND} from 'baseui/button';
import {useDispatch, useSelector} from "react-redux";
import ConferenceCard from "../ConferenceCard/ConferenceCard";
import AddEditConferenceModal from "../AddEditConferenceModal/AddEditConferenceModal";
import AddSectionModal from "../AddSectionModal/AddSectionModal";
import AttendConferenceModal from "../AttendConferenceModal/AttendConferenceModal";
import UploadPresentationModal from "../UploadPresentationModal/UploadPresentationModal";


const ConferenceSection = () => {
    const dispatch = useDispatch();
    const locations = [
        {title: 'My Conferences', itemId: '/dashboard/conferences/my-conferences',},
        {title: 'Attend Conference', itemId: '/dashboard/conferences/attend-conference'},
        {title: 'Upload Presentation', itemId: '/dashboard/conferences/upload-presentation'},
        {title: 'Add Section', itemId: '/dashboard/conferences/add-section'}
    ];
    const [modalOpen, setModalOpen] = useState(false);
    const conferences = useSelector(state => state.conference.conferences);

    return (
        <div className={"ConferenceSection"}>
            <SectionNavigation locations={locations}/>
            <Switch>
                <Route
                    exact
                    path={'/dashboard/conferences/:subsection(my-conferences)'}
                    render={(props) =>
                        <>
                            <ListContainer {...props}>
                                <Button kind={BUTTON_KIND.secondary} style={{width: '50%'}} onClick={() => {
                                    /*
                                    Non-null proposal context implies that
                                    AddEditProposalModal should operate in edit mode.
                                    */
                                    dispatch({type: RESET_CONTEXT_PROPOSAL});
                                    setModalOpen(true);
                                }}>
                                    Add Conference
                                </Button>
                                {
                                    conferences.map(c =>
                                        <ConferenceCard
                                            key={c.id}
                                            navProps={props}
                                            conference={c}
                                            setModalOpen={setModalOpen}
                                        />)
                                }
                            </ListContainer>
                            <AddEditConferenceModal modalOpen={modalOpen} setModalOpen={setModalOpen}/>
                        </>
                    }
                />

                <Route
                    exact
                    path={'/dashboard/conferences/:subsection(upload-presentation)'}
                    render={(props) =>
                        <>
                            <ListContainer {...props}>
                                {
                                    conferences.map(c =>
                                        <ConferenceCard
                                            key={c.id}
                                            navProps={props}
                                            conference={c}
                                            setModalOpen={setModalOpen}
                                        />)
                                }
                            </ListContainer>
                            <UploadPresentationModal
                                uploadPresentation={true}
                                modalOpen={modalOpen}
                                setModalOpen={setModalOpen}/>
                        </>
                    }
                />

                <Route
                    exact
                    path={'/dashboard/conferences/:subsection(attend-conference)'}
                    render={(props) =>
                        <>
                            <ListContainer {...props}>
                                {
                                    conferences.map(c =>
                                        <ConferenceCard
                                            key={c.id}
                                            navProps={props}
                                            conference={c}
                                            setModalOpen={setModalOpen}
                                        />)
                                }
                            </ListContainer>
                            <AttendConferenceModal modalOpen={modalOpen} setModalOpen={setModalOpen}/>
                        </>
                    }
                />

                <Route
                    exact
                    path={'/dashboard/conferences/:subsection(add-section)'}
                    render={(props) =>
                        <>
                            <ListContainer {...props}>
                                {
                                    conferences.map(c =>
                                        <ConferenceCard
                                            key={c.id}
                                            navProps={props}
                                            conference={c}
                                            setModalOpen={setModalOpen}
                                        />)
                                }
                            </ListContainer>
                            <AddSectionModal modalOpen={modalOpen} setModalOpen={setModalOpen}/>
                        </>
                    }
                />

                <Route path={'*'} component={NotFound}/>
            </Switch>
        </div>
    );
};

ConferenceSection.propTypes = {};

ConferenceSection.defaultProps = {};

export default ConferenceSection;
