import React, {useState} from "react";

import './ProposalSection.css';
import SectionNavigation from "../../navigation/SectionNavigation/SectionNavigation";
import {Route, Switch} from "react-router-dom";
import NotFound from "../../navigation/NotFound/NotFound";
import ListContainer from "../../generic/ListContainer/ListContainer";
import ProposalCard from "../ProposalCard/ProposalCard";
import BidModal from "../BidModal/BidModal";
import ReviewProposalModal from "../ReviewProposalModal/ReviewProposalModal";
import ResolveProposalModal from "../ResolveProposalModal/ResolveProposalModal";
import {useDispatch, useSelector} from "react-redux";
import AddEditProposalModal from "../AddEditProposalModal/AddEditProposalModal";
import {Button, KIND as BUTTON_KIND} from "baseui/button";
import {RESET_CONTEXT_PROPOSAL} from "../../../redux/context/contextActions";
import AssignReviewersModal from "../AssignReviewersModal/AssignReviewersModal";

const ProposalSection = () => {
    const dispatch = useDispatch();
    const proposals = useSelector(state => state.proposal.proposals);
    const [modalOpen, setModalOpen] = useState(false);

    const locations = [
        {title: 'My Proposals', itemId: '/dashboard/proposals/my-proposals'},
        {title: 'Bidding', itemId: '/dashboard/proposals/bidding'},
        {title: 'Review', itemId: "/dashboard/proposals/review"},
        {title: 'Resolve', itemId: '/dashboard/proposals/resolve'},
        {title: 'Improve Proposals', itemId: '/dashboard/proposals/improve'},
        {title: 'Assign Reviewers', itemId: '/dashboard/proposals/assign-reviewers'}
    ];

    return (
        <div className={"ProposalSection"}>
            <SectionNavigation locations={locations}/>
            <Switch>
                <Route
                    exact
                    path={'/dashboard/proposals/:subsection(my-proposals)'}
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
                                    Add Proposal
                                </Button>
                                {
                                    proposals.map(p =>
                                        <ProposalCard
                                            key={p.id}
                                            navProps={props}
                                            proposal={p}
                                            setModalOpen={setModalOpen}
                                        />)
                                }
                            </ListContainer>
                            <AddEditProposalModal modalOpen={modalOpen} setModalOpen={setModalOpen}/>
                        </>
                    }
                />

                <Route
                    exact
                    path={'/dashboard/proposals/:subsection(bidding)'}
                    render={(props) =>
                        <>
                            <ListContainer {...props}>
                                {
                                    proposals.map(p =>
                                        <ProposalCard
                                            key={p.id}
                                            navProps={props}
                                            proposal={p}
                                            setModalOpen={setModalOpen}
                                        />)
                                }
                            </ListContainer>
                            <BidModal modalOpen={modalOpen} setModalOpen={setModalOpen}/>
                        </>
                    }
                />

                <Route
                    exact
                    path={'/dashboard/proposals/:subsection(review)'}
                    render={(props) =>
                        <>
                            <ListContainer {...props}>
                                {
                                    proposals.map(p =>
                                        <ProposalCard
                                            key={p.id}
                                            navProps={props}
                                            proposal={p}
                                            setModalOpen={setModalOpen}
                                        />)
                                }
                            </ListContainer>
                            <ReviewProposalModal modalOpen={modalOpen} setModalOpen={setModalOpen}/>
                        </>
                    }
                />

                <Route
                    exact
                    path={'/dashboard/proposals/:subsection(resolve)'}
                    render={(props) =>
                        <>
                            <ListContainer {...props}>
                                {
                                    proposals.map(p =>
                                        <ProposalCard
                                            key={p.id}
                                            navProps={props}
                                            proposal={p}
                                            setModalOpen={setModalOpen}
                                        />)
                                }
                            </ListContainer>
                            <ResolveProposalModal modalOpen={modalOpen} setModalOpen={setModalOpen}/>
                        </>
                    }
                />

                <Route
                    exact
                    path={'/dashboard/proposals/:subsection(improve)'}
                    render={props =>
                        <>
                            <ListContainer {...props}>
                                {
                                    proposals.map(p =>
                                        <ProposalCard
                                            key={p.id}
                                            navProps={props}
                                            proposal={p}
                                            setModalOpen={setModalOpen}
                                        />)
                                }
                            </ListContainer>
                            <AddEditProposalModal
                                improveScenario={true}
                                modalOpen={modalOpen}
                                setModalOpen={setModalOpen}
                            />
                        </>
                    }
                />
                <Route
                    exact
                    path={'/dashboard/proposals/:subsection(assign-reviewers)'}
                    render={props =>
                        <>
                            <ListContainer {...props}>
                                {
                                    proposals.map(p =>
                                        <ProposalCard
                                            key={p.id}
                                            navProps={props}
                                            proposal={p}
                                            setModalOpen={setModalOpen}
                                        />)
                                }
                            </ListContainer>
                            <AssignReviewersModal
                                modalOpen={modalOpen}
                                setModalOpen={setModalOpen}
                            />
                        </>
                    }
                />

                <Route path={'*'} component={NotFound}/>
            </Switch>
        </div>
    );
};

export default ProposalSection;
